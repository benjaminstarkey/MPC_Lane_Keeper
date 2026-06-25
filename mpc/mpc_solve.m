function [u_optimal, u_horizon] = mpc_solve(x_k, F, Phi, Np, Nc, Q, R, u_max)

Nx = size(Q,1);
Nu = size(R,1);

% Stack Q across the prediction horizon Np -> (Np*nx x Np*nx)
Q_bar = kron(eye(Np), Q);
% Stack R across the control horizon Nc -> (Nc*nu x Nc*nu)
R_bar = kron(eye(Nc), R);

% QP Matrices: 0.5*U'*H_qp*U + f_qp'*U
H_qp = 2*(Phi'*Q_bar*Phi + R_bar);
H_qp = (H_qp + H_qp') / 2; % ensure numerical skew-sym
f_qp = 2*Phi'*Q_bar*F*x_k;

u_lb = -u_max * ones(Nc*Nu, 1);
u_ub = u_max * ones(Nc*Nu, 1);

% QP options, ensure suppress for speed
options = optimoptions('quadprog', 'Display', 'off');

% QP Optimization Solver
[u_horizon, ~, exitflag] = quadprog(H_qp, f_qp, [], [], [], [], u_lb, u_ub, [], options);

if exitflag < 1
    warning('MPC Solver failed to find an optimal solution. Defaulting to 0 steering.');
    u_horizon = zeros(Nc * nu, 1);
end

u_optimal = u_horizon(1:Nu);


end