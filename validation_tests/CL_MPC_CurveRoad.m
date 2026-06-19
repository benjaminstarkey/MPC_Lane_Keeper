%% CL Dynamic Test for Straight Road MPC & KF Validation

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
[Ad, Bd, Ed] = bicycle_dynamics(m, Izz, Vx, Cf, Cr, lf, lr, dt);

% Initialize prediction and control horizon steps
Np = 20;
Nc = 5;

% Generate mpc matrices F (state-horizon) and Phi (control-horizon)
[F, Phi, Gamma] = build_mpc_matrices(Ad, Bd, Ed, Np, Nc);



% Initialize for Lane Keeping MPC Simulation
max_turn = deg2rad(25);

Q_mpc = diag([10, 1, 50, 5]);
R_mpc = 0.1;

sim_time = 8;
t_steps = sim_time/dt;
t_vec = 0:dt:sim_time;

x_k = [-0.7; 0.2; deg2rad(4); -0.1]; % initial offset state


% Kalman Filter Initializing
x_hat = [1; 0; deg2rad(0.5); 0];
P_hat = diag([5, 5, 5, 5]);
last_u = 0; % Initially 0 control input

H = [1, 0, 0, 0;
     0, 0, 1, 0]; % only measure e1, e2
Q_kf = diag([1e-5, 1e-3, 1e-4, 1e-3]);
R_kf = diag([0.08.^2, deg2rad(3).^2]);

process_noise = [0.001; 0.003; deg2rad(0.3); deg2rad(0.1)];
sensor_noise = [0.1; deg2rad(1)];

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

% State and input 
x_true_vec = zeros(t_steps + 1, 4); % pre-allocate state history
x_true_vec(1, :) = x_k'; % place x0 for first state

x_hat_vec = zeros(t_steps + 1, 4); % pre-allocate estimation history
x_hat_vec(1, :) = x_hat'; % place x_hat0 for first state

x_meas_vec = zeros(t_steps + 1, 2); % pre-allocate measurement history
u_vec = zeros(t_steps, 1); % pre-allocate input history

%% Curved Road Plotting

% Put road curve into global coords for centerline
X_road = zeros(length(rho),1);
Y_road = zeros(length(rho),1);
theta_road = zeros(length(rho),1);
for i = 1:length(rho)-1
    theta_road(i+1) = Vx*rho(i)*dt + theta_road(i); % integrate with psi_dot
    X_road(i+1) = Vx*cos(theta_road(i))*dt + X_road(i);
    Y_road(i+1) = Vx*sin(theta_road(i))*dt + Y_road(i);
end

% Global Coords
global_X = zeros(t_steps + 1, 1);
global_Y = zeros(t_steps + 1, 1);
global_X(1) = X_road(1) - x_k(1)*sin(theta_road(1));
global_Y(1) = Y_road(1) + x_k(1)*cos(theta_road(1));

% Figure
figure('Name', 'MPC Lateral Lane Keeper Test Simulation', 'NumberTitle', 'off', 'Position', [100, 100, 1000, 500]);
hold on; grid on; axis equal; % added axis equal so curves don't look warped
lane_width = 3.6; % emulate highway width

% Draw Lane Boundaries
X_left = X_road - (lane_width/2) * sin(theta_road);
Y_left = Y_road + (lane_width/2) * cos(theta_road);
X_right = X_road + (lane_width/2) * sin(theta_road);
Y_right = Y_road - (lane_width/2) * cos(theta_road);

plot(X_left, Y_left, 'k-', 'LineWidth', 2);     % Left edge
plot(X_right, Y_right, 'k-', 'LineWidth', 2);   % Right edge
plot(X_road, Y_road, 'r--', 'LineWidth', 1);    % Centerline Reference

% Create persistent animation handles
hCarBody = plot(0, 0, 'Square', 'MarkerSize', 15, 'MarkerFaceColor', 'b', 'MarkerEdgeColor', 'k');
hTrajectory = plot(NaN, NaN, 'b-', 'LineWidth', 1.5); % Actual historical path
hHorizonTail = plot(NaN, NaN, 'g-o', 'LineWidth', 1.5, 'MarkerSize', 4, 'MarkerFaceColor', 'g'); % MPC prediction

title('Real-Time Lateral Vehicle Dynamics Tracking (Global S-Curve)');
xlabel('Global Position X [meters]');
ylabel('Lateral Deviation Y [meters]');

% axis([-5, Vx*sim_time + 10, -3, 3]);
% ylim([-2.5, 2.5])


%% Control Loop

for k = 1:t_steps

%%% 1. Kalman Filter %%%
% Simultate plant w process noise
x_true = Ad*x_k + Bd*last_u + Ed*rho(k) + process_noise .* randn(4,1); % true states + process noise

% Simultaed Measurements of e1, e2
x_meas = H*x_true + sensor_noise .* randn(2,1);

% KF State Estimation
[x_hat, P_hat, K_kf] = kalman_filter(x_hat, last_u, P_hat, rho(k), x_meas, Ad, Bd, Ed, H, Q_kf, R_kf);



%%% 2. Quadratic Programming Optimization for MPC %%%
rho_preview = rho(k+1:k+Np); % preview next Np curve entries for MPC

% Solve QP for u_horizon to plot planned trajectory
[u_opt, u_horz] = mpc_solve(x_hat, F, Phi, Gamma, rho_preview, Np, Nc, Q_mpc, R_mpc, max_turn);

% Get planned mpc trajectory
Y_mpc = F*x_hat + Phi*u_horz + Gamma*rho_preview;



%%% 3. Response Plotting and Animation
% Store for plotting
x_true_vec(k+1,:) = x_true'; % store true states
x_hat_vec(k+1,:) = x_hat'; % store estimated states
x_meas_vec(k+1,:) = x_meas'; % store measured states e1, e2
u_vec(k) = u_opt; % store optimal steer input

% Transform state errors to global for plotting
global_X(k+1) = -x_true(1) * sin(theta_road(k+1)) + X_road(k+1);
global_Y(k+1) = x_true(1) * cos(theta_road(k+1)) + Y_road(k+1);

% Compute mpc horizon path in global frame
pred_Y = zeros(Np, 1);
pred_X = zeros(Np, 1);
for j = 1:Np
    pred_idx = k+1+j;
    e1_pred = Y_mpc((j-1)*4 + 1); % Extract e1 @ each horizon step p

    % Integrate rotated e1 in global frame
    pred_X(j) = -e1_pred * sin(theta_road(pred_idx)) + X_road(pred_idx);  
    pred_Y(j) = e1_pred * cos(theta_road(pred_idx)) + Y_road(pred_idx);
end

set(hCarBody, 'XData', global_X(k+1), 'YData', global_Y(k+1));
set(hTrajectory, 'XData', global_X(1:k+1), 'YData', global_Y(1:k+1));
set(hHorizonTail, 'XData', pred_X, 'YData', pred_Y);

% Dynamic camera window following the car
xlim([global_X(k+1) - 20, global_X(k+1) + 40]);
ylim([global_Y(k+1) - 10, global_Y(k+1) + 20]);

drawnow; % Flush drawing buffer
pause(0.02); % Control frame rate

% Update state and input for next iteration
x_k = x_true;
last_u = u_opt;

end

figure('Name', 'MPC Performance Diagnostics', 'NumberTitle', 'off');
subplot(3,1,1); hold on; grid on;
plot(t_vec, x_true_vec(:,1), 'k', 'LineWidth', 1.5);
plot(t_vec, x_hat_vec(:,1), 'b', 'LineWidth', 1);
plot(t_vec, x_meas_vec(:,1), 'r.', 'MarkerSize', 5);
ylabel('Lateral Error e_1 [m]');
title('Closed-Loop Diagnostics');
legend('True Lateral Error (e1)', 'KF Estimated e1', 'Noisy Sensor Reading');

subplot(3,1,2); hold on; grid on;
plot(t_vec, rad2deg(x_true_vec(:,3)), 'k', 'LineWidth', 1.5);
plot(t_vec, rad2deg(x_hat_vec(:,3)), 'b', 'LineWidth', 1);
plot(t_vec, rad2deg(x_meas_vec(:,2)), 'r.', 'MarkerSize', 5);
ylabel('Heading Error e_2 [deg]');
legend('True Heading Error (e2)', 'KF Estimated e2', 'Noisy Sensor Reading');

subplot(3,1,3);
plot(t_vec(1:end-1), rad2deg(u_vec), 'k', 'LineWidth', 1.5); grid on;
xlabel('Time [seconds]');
ylabel('Steering Input \delta [deg]');
legend('Steer Command')

disp('Animation complete; diagnostics plotted');