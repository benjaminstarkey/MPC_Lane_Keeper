%% Simulink Initialization Script
clear
clc





%% Plant Dynamics
% CAN TRY MISMATCH FOR ROBUSTNESS ANALYSIS
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

%% Bike Kalman Filter

x_hat_0 = [1; 0; deg2rad(0.5); 0];
P_hat_0 = diag([5, 5, 5, 5]);
last_u = 0; % Initially 0 control input

H = [1, 0, 0, 0;
     0, 0, 1, 0]; % only measure e1, e2
Q_kf = diag([1e-5, 1e-3, 1e-4, 1e-3]);
R_kf = diag([0.08.^2, deg2rad(3).^2]);

process_noise = [0.001; 0.003; deg2rad(0.3); deg2rad(0.1)];
sensor_noise = [0.1; deg2rad(1)];

process_noise_power = process_noise.^2 .* dt;
sensor_noise_power = sensor_noise.^2 .* dt;

%% MPC Parameters
Np = 20;
Nc = 5;

% Generate mpc matrices F (state-horizon) and Phi (control-horizon)
[F, Phi, Gamma] = build_mpc_matrices(Ad, Bd, Ed, Np, Nc);

Q_mpc = diag([10, 1, 50, 5]);
R_mpc = 0.1;

max_turn = deg2rad(25);

%% LQR Control for Comparison
Q_lqr = diag([10, 1, 50, 5]);
R_lqr = 0.1;

K_lqr = dlqr(Ad, Bd, Q_lqr, R_lqr);

%% Road Curvature Disturbance Rho

% Simulation Parameters
sim_time = 8;
t_steps = sim_time/dt;
t_vec = 0:dt:sim_time;

% Build road curvature profile
rho = zeros(t_steps+Np+10,1);
for i = 1:length(rho)
    t_road = i*dt;
    if t_road >= 1.5 && t_road < 3
        rho(i) = 0.035; % 1/r, r = 400m
    elseif t_road >= 4 && t_road < 5.5
        rho(i) = -0.035;
    end
end


rho_k_vec = [t_vec', rho(1:length(t_vec'))];


preview_data = zeros(length(t_vec'), Np);
for k = 1:length(t_vec')
    preview_data(k, :) = rho(k : k + Np - 1)';
end
rho_preview_vec = [t_vec', preview_data];