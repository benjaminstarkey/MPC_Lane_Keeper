function [F, Phi, Gamma] = build_mpc_matrices(Ad, Bd, Ed, Np, Nc)

% Ad = discrete A matrix
% Bd = discrete B matrix
% Np = prediction horizon, number of lookahead steps
% Nc = control horizon, number of optimized steering cmds

Nx = size(Ad,1); % number of states (4)
Nu = size(Bd,2); % number of inputs (1, steering angle))
Nd = size(Ed,2); % number of disturbances (1, road curvature)

% Pre-allocate Matrix Sizes
F = zeros(Np*Nx, Nx);
Phi = zeros(Np*Nx, Nc*Nu);
Gamma = zeros(Np*Nx, Nd*Nu);

% Build F matrix, maps current states to future
for i = 1:Np
    F((i-1)*Nx+1:i*Nx,:) = Ad^i;
end

% Toeplitz structure
% Maps control inputs to future states
for i = 1:Np
    for j = 1:Nc
        if i >= j
            Phi((i-1)*Nx+1:i*Nx, (j-1)*Nu+1:j*Nu) = (Ad^(i-j))*Bd;
        end
    end
end

% Maps road distrubances to future states
for i = 1:Np
    for j = 1:Np
        if i >= j
            Gamma((i-1)*Nx+1:i*Nx, (j-1)*Nd+1:j*Nd) = (Ad^(i-j))*Ed;
        end
    end
end


end