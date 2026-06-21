%% Simulink Initialization Script
clear
clc





%% Plant Dynamics
% Bike Dynamic Parameters
m = 1500; % (kg), mass
Izz = 3000; % (kg*m^2), inertia about birds-eye z axis
Vx = 20; % (m/s), forward longitudinal velocity

Cf = 40000; %(N/rad/tire), front tire turn stiffness (virtual of both front)
Cr = 40000; %(N/rad/tire), rear tire turn stiffness (virtual of both rear)
lf = 1.2; % (m), distance from COM to front tire
lr = 1.6; % (m), distance from COM to rear tire

% Discrete Dynamics Time Step
dt = 0.05; % 20Hz

% Generate discrete dynamic and control matrices (A,B)
[Ad, Bd, Ed, Cd, Dd] = bicycle_dynamics(m, Izz, Vx, Cf, Cr, lf, lr, dt);

x_0 = [-0.7; 0.2; deg2rad(4); -0.1]; % initial offset state


%% Test:
mux_input = [0.2; 0.05]
for i = 1
    x_1 = Ad*x_0 + [Bd, Ed] * [mux_input];
    y_out = Cd*x_1 + Dd*[mux_input]
end

y_out
