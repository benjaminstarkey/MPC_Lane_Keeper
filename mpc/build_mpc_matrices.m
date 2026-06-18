function [F, Phi] = build_mpc_matrices(Ad, Bd, Np, Nc)

% Ad = discrete A matrix
% Bd = discrete B matrix
% Np = prediction horizon, number of lookahead steps
% Nc = control horizon, number of optimized steering cmds

Nx = size(Ad,1); % number of states (4)
Nu = size(Bd,2); % number of inputs (1)

F = zeros(Np*Nx, Nx);
Phi = zeros(Np*Nx, Nc*Nu);

% Build F matrix
for i = 1:Np
    F((i-1)*Nx+1:i*Nx,:) = Ad^i;
end

% Toeplitz structure
for i = 1:Np
    for j = 1:Nc
        if i >= j
            Phi((i-1)*Nx+1:i*Nx, (j-1)*Nu+1:j*Nu) = (Ad^(i-j))*Bd;
        end
    end
end


end