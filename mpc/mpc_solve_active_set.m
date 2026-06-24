function [u_optimal, u_horizon] = mpc_solve_active_set(x_k, F, Phi, Gamma, rho_preview, Q, R, u_max)
%#codegen

% Use mpcActiveSetSolver over quadprog for code generation

% Assert static allocation for inputs (codegen)
assert(all(size(x_k) == [4, 1]));
assert(all(size(F) == [80, 4]));
assert(all(size(Phi) == [80, 5]));
assert(all(size(Gamma) == [80, 20]));
assert(all(size(rho_preview) == [20, 1]));
assert(all(size(Q) == [4, 4]));
assert(all(size(R) == [1, 1]));
assert(all(size(u_max) == [1, 1]));

% Know that 
    % Np = 20
    % Nc = 5
    % but must use literals over dynamic inputs for codegen

% Establish state and input sizes
    % Nx = 4;
    % Nu = 1;

% Stack Q across the prediction horizon Np -> (Np*nx x Np*nx) use literals
Q_bar = kron(eye(20), Q); % Np = 20
% Stack R across the control horizon Nc -> (Nc*nu x Nc*nu)
R_bar = kron(eye(5), R); % Nc = 5

% QP Matrices: 0.5*U'*H_qp*U + f_qp'*U
    % Hessian H: 
    % Gradient f: acts as feedforward control to upcoming curve disturbances
H_qp = 2*(Phi'*Q_bar*Phi + R_bar);
H_qp = (H_qp + H_qp') / 2; % ensure numerical skew-sym
f_qp = 2*Phi'*Q_bar*(F*x_k + Gamma*rho_preview);

% Ensure static sizes for H and f matrices
assert(all(size(H_qp) == [5, 5]));
assert(all(size(f_qp) == [5, 1]));

% mpcActiveSetSolver setup for constraints: A_ineq * U >= b_ineq
A_ineq = [eye(5); -eye(5)];
b_ineq = [u_max * ones(5, 1); 
          u_max * ones(5, 1)];

% Ensure static memory for A_ineq, b_ineq
assert(all(size(A_ineq) == [10, 5]));
assert(all(size(b_ineq) == [10, 1]));

persistent iA0_prev;
    
% Cold start on the very first loop iteration
if isempty(iA0_prev)
   iA0_prev = false(10, 1); % Preallocate with static literal sizing
end

% options = mpcActiveSetOptions;
% options.MaxIterations = 120; % stop regardless after 120 iterations

% Establish codegen safe options for activeSetSolver
options.MaxIterations = 120;
options.ConstraintTolerance = 1e-6;
options.UseHessianAsInput = true; % Pre-computed Hessian mode
options.FeasibilityTolerance = 1e-6;
options.IntegrityChecks = false;  % Turn off checks for maximum Teensy loop speed

A_eq = zeros(0, 5);
b_eq = zeros(0, 1);


% QP Optimization Solver
[u_horizon, status, iA_out] = mpcActiveSetSolver(H_qp, f_qp, A_ineq, b_ineq, A_eq, b_eq, iA0_prev, options);

% Ensure static memory of outputs
assert(all(size(u_horizon) == [5, 1]));
assert(all(size(iA_out) == [10, 1]));

% Update persistent memory for next step
iA0_prev(:) = iA_out;

if status <= 0
    % warning('MPC Solver failed to find an optimal solution. Defaulting to 0 steering.');
    u_horizon = zeros(5, 1);
end

% Extract optimal steering commands
u_optimal = u_horizon(1);

end