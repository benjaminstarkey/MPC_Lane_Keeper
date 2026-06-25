%% CL Dynamic Test for Straight Road MPC Validation

m = 1500; % (kg), mass
Izz = 3000; % (kg*m^2), inertia about birds-eye z axis
Vx = 20; % (m/s), forward longitudinal velocity

Cf = 40000; %(N/rad/tire), front tire turn stiffness (virtual of both front)
Cr = 40000; %(N/rad/tire), rear tire turn stiffness (virtual of both rear)
lf = 1.2; % (m), distance from COM to front tire
lr = 1.6; % (m), distance from COM to rear tire

% Generate discrete dynamic and control matrices (A,B)
[Ad, Bd] = bicycle_dynamics(m, Izz, Vx, Cf, Cr, lf, lr);

% Initialize prediction and control horizon steps
Np = 20;
Nc = 5;

% Generate mpc matrices F (state-horizon) and Phi (control-horizon)
[F, Phi] = build_mpc_matrices(Ad, Bd, Np, Nc);

%%% Initialize for Lane Keeping MPC Simulation %%%
max_turn = deg2rad(25);

Q = diag([10, 1, 50, 1]);
R = 0.5;

sim_time = 3;
t_steps = sim_time/dt;
t_vec = 0:dt:sim_time;

x_k = [1.5; 0.3; deg2rad(0); 4]; % initial offset state

% State and input 
x_vec = zeros(t_steps + 1, 4); % pre-allocate state history
x_vec(1, :) = x_k'; % place x0 for first state
u_vec = zeros(t_steps, 1); % pre-allocate input history

% Global coords
global_X = zeros(t_steps + 1, 1);
global_Y = zeros(t_steps + 1, 1);
global_Y(1) = x_k(1); % Initial lateral deviation

% Figure
figure('Name', 'MPC Lateral Lane Keeper Test Simulation', 'NumberTitle', 'off', 'Position', [100, 100, 1000, 500]);
hold on; grid on;

lane_width = 3.6; % emulate highway width
plot([-10, Vx*sim_time + 20], [lane_width/2, lane_width/2], 'k-', 'LineWidth', 2);     % Left edge
plot([-10, Vx*sim_time + 20], [-lane_width/2, -lane_width/2], 'k-', 'LineWidth', 2);   % Right edge
plot([-10, Vx*sim_time + 20], [0, 0], 'r--', 'LineWidth', 1);                          % Centerline Reference

% Create persistent animation handles
hCarBody = plot(0, 0, 'Square', 'MarkerSize', 15, 'MarkerFaceColor', 'b', 'MarkerEdgeColor', 'k');
hTrajectory = plot(NaN, NaN, 'b-', 'LineWidth', 1.5); % Actual historical path
hHorizonTail = plot(NaN, NaN, 'g-o', 'LineWidth', 1.5, 'MarkerSize', 4, 'MarkerFaceColor', 'g'); % MPC prediction

title('Real-Time Lateral Vehicle Dynamics Tracking (Closed-Loop MPC)');
xlabel('Global Position X [meters]');
ylabel('Lateral Deviation Y [meters]');
axis([-5, Vx*sim_time + 10, -3, 3]);
ylim([-2.5, 2.5])

for k = 1:t_steps
% Solve QP for u_horizon to plot planned trajectory
[u_opt, u_horz] = mpc_solve(x_k, F, Phi, 20, 5, Q, R, max_turn);

% Get planned mpc trajectory
Y_mpc = F*x_k + Phi*u_horz;

% Update actual bike dynamics
x_next = Ad*x_k + Bd*u_opt;

% Store for plotting
x_vec(k+1,:) = x_next'; % store states
u_vec(k) = u_opt; % store optimal steer input

% Transform state errors to global for plotting
global_X(k+1) = Vx*dt + global_X(k); % integrate linear x vel
global_Y(k+1) = x_next(1); % lateral position rel to 0 centerline

% Compute mpc horizon path in global frame
pred_Y = zeros(Np, 1);
pred_X = zeros(Np, 1);
for p = 1:Np
    pred_X(p) = global_X(k+1) + (p * Vx * dt); % linear euler x pos update
    pred_Y(p) = Y_mpc((p-1)*4 + 1); % Extract e1 @ each horizon step p
end

set(hCarBody, 'XData', global_X(k+1), 'YData', global_Y(k+1));
set(hTrajectory, 'XData', global_X(1:k+1), 'YData', global_Y(1:k+1));
set(hHorizonTail, 'XData', pred_X, 'YData', pred_Y);

xlim([global_X(k+1) - 35, global_X(k+1) + 55]);

drawnow; % Flush drawing buffer
pause(0.02); % Control frame rate

% Update state for next iteration
x_k = x_next;

end


% Diagnostic Plots
figure('Name', 'MPC Performance Diagnostics', 'NumberTitle', 'off');
subplot(3,1,1);
plot(t_vec, x_vec(:,1), 'r', 'LineWidth', 2); grid on;
ylabel('Lateral Error e_1 [m]');
title('Closed-Loop Diagnostics');

subplot(3,1,2);
plot(t_vec, rad2deg(x_vec(:,3)), 'g', 'LineWidth', 2); grid on;
ylabel('Heading Error e_2 [deg]');

subplot(3,1,3);
plot(t_vec(1:end-1), rad2deg(u_vec), 'b', 'LineWidth', 2); grid on;
xlabel('Time [seconds]');
ylabel('Steering Input \delta [deg]');

display('Animation complete; diagnostics plotted')