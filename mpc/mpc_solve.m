function [u_optimal, u_horizon] = mpc_solve_active_set(x_k, F, Phi, Gamma, rho_preview, Np, Nc, Q, R, u_max)
%#codegen

% Use mpcActiveSetSolver over quadprog for code generation

% Get Sizes from Q and R matrices for horizon lengths
Nx = size(Q,1);
Nu = size(R,1);

% Stack Q across the prediction horizon Np -> (Np*nx x Np*nx)
Q_bar = kron(eye(Np), Q);
% Stack R across the control horizon Nc -> (Nc*nu x Nc*nu)
R_bar = kron(eye(Nc), R);

% QP Matrices: 0.5*U'*H_qp*U + f_qp'*U
    % Hessian H: 
    % Gradient f: acts as feedforward control to upcoming curve disturbances
H_qp = 2*(Phi'*Q_bar*Phi + R_bar);
H_qp = (H_qp + H_qp') / 2; % ensure numerical skew-sym
f_qp = 2*Phi'*Q_bar*(F*x_k + Gamma*rho_preview);

% u_lb = -u_max * ones(Nc*Nu, 1);
% u_ub = u_max * ones(Nc*Nu, 1);

% mpcActiveSetSolver setup: A_ineq * U >= b_ineq
I_nc = eye(Nc * nu);
A_ineq = [I_nc; -I_nc];
b_ineq = [-delta_max * ones(Nc * nu, 1); 
          -delta_max * ones(Nc * nu, 1)];

persistent iA0_prev;
    
% Cold start on the very first loop iteration
if isempty(iA0_prev)
   iA0_prev = false(size(b_ineq)); 
end

options = mpcActiveSetSolverOptions;
options.MaxIterations = 120; % stop regardless after 120 iterations

A_eq = zeros(0, Nc * nu);
b_eq = zeros(0, 1);

% QP options, ensure suppress for speed
% options = optimoptions('quadprog', 'Display', 'off');

% QP Optimization Solver
[u_horizon, status, iA_out] = mpcActiveSetSolver(H_qp, f_qp, A_ineq, b_ineq, A_eq, b_eq, iA0_prev, options);

% Update persistent memory for next step
iA0_prev = iA_out;

if status <= 0
    warning('MPC Solver failed to find an optimal solution. Defaulting to 0 steering.');
    u_horizon = zeros(Nc * nu, 1);
end

% Extract optimal steering commands
u_optimal = u_horizon(1:Nu);

end