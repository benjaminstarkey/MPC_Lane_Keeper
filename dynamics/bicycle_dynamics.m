%% Equations of Motion for Bicycle Model

% STATES REL TO CENTERLINE (not inertial)
    % e1: lateral position error from centerline
    % e1_dot: lateral velocity error
    % e2: heading angle error from centerline
    % e2_dot: heading angular velocity error (e3_dot)

% Notebook has written dynamics derivations

m = 1500; % (kg), mass
Izz = 3000; % (kg*m^2), inertia about birds-eye z axis
Vx = 20; % (m/s), forward longitudinal velocity

Cf = 40000; %(N/rad/tire), front tire turn stiffness (virtual of both front)
Cr = 40000; %(N/rad/tire), rear tire turn stiffness (virtual of both rear)
lf = 1.2; % (m), distance from COM to front tire
lr = 1.6; % (m), distance from COM to rear tire


% State Space Matrices
A = [0, 1, 0, 0;
     0, (-2*(Cf+Cr))/(m*Vx), (2*(Cf+Cr))/m, (-2*(Cf*lf-Cr*lr))/(m*Vx);
     0, 0, 0, 1;
     0, (-2*(Cf*lf-Cr*lr))/(Izz*Vx), (2*(Cf*lf-Cr*lr))/Izz, (-2*(Cf*lf^2+Cr*lr^2))/(Izz*Vx)]

B = [0; 2*Cf/m; 0; 2*Cf*lf/Izz]

E = [0; (-2*(Cf*lf-Cr*lr))/m - Vx^2; 0; (-2*(Cf*lf^2+Cr*lr^2))/Izz]

C = eye(4)
D = zeros(4,1)

%% OL Dynamics Check
sys_c = ss(A, B, C, D);

% Run a step response with a 0.035 rad (2 degree) steering input
t = 0:0.01:5; % 5 second timespan
u = 0.035 * ones(size(t)); % Constant front steering angle
[y, t, x] = lsim(sys_c, u, t);

figure
subplot(2,1,1)
plot(t, x(:,1))
title('Lateral Error (e_1) [m]')
grid on

subplot(2,1,2)
plot(t, x(:,3))
title('Heading Error (e_2) [rad]')
grid on


%% Discrete Time State Space
dt = 0.05

sys_d = c2d(sys_c, dt, 'zoh') % zoh for discrete and eventual PIL test
