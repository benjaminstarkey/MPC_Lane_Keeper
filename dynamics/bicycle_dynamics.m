%% Equations of Motion for Bicycle Model

% STATES REL TO CENTERLINE (not inertial)
    % e1: lateral position error from centerline
    % e1_dot: lateral velocity error
    % e2: heading angle error from centerline
    % e2_dot: heading angular velocity error (e3_dot)

% Notebook has written dynamics derivation

function [Ad, Bd, Ed] = bicycle_dynamics(m, Izz, Vx, Cf, Cr, lf, lr, dt)

% m (kg), mass
% Izz (kg*m^2), inertia about birds-eye z axis
% Vx (m/s), forward longitudinal velocity

% Cf (N/rad/tire), front tire turn stiffness (virtual of both front)
% Cr (N/rad/tire), rear tire turn stiffness (virtual of both rear)
% lf (m), distance from COM to front tire
% lr (m), distance from COM to rear tire


% State Space Matrices
A = [0, 1, 0, 0;
     0, (-2*(Cf+Cr))/(m*Vx), (2*(Cf+Cr))/m, (-2*(Cf*lf-Cr*lr))/(m*Vx);
     0, 0, 0, 1;
     0, (-2*(Cf*lf-Cr*lr))/(Izz*Vx), (2*(Cf*lf-Cr*lr))/Izz, (-2*(Cf*lf^2+Cr*lr^2))/(Izz*Vx)];

B = [0; 2*Cf/m; 0; 2*Cf*lf/Izz];

E = [0; (-2*(Cf*lf-Cr*lr))/m - Vx^2; 0; (-2*(Cf*lf^2+Cr*lr^2))/Izz];
% Need to add discrete E in future for curved road

C = eye(4); % Eventual EKF...
D = zeros(4,1);

% Combine B and E for curved road tracking
B_combined = [B, E];

sys_c = ss(A, B_combined, C, [D, zeros(4,1)]);

% Discrete Time State Space
sys_d = c2d(sys_c, dt, 'zoh'); % zoh for discrete and eventual PIL test

Ad = sys_d.A; % 4x4
Bd = sys_d.B(:,1); % 4x1
Ed = sys_d.B(:,2); % 4x1

end