%% Bike Animation Post-processing from Simulink

% Grab data from out struct
sim_t = out.tout;

x_true_vec = out.x_true_vec.data;
x_hat_vec = out.x_hat_vec.data;
u_optimal = out.u_opt.data;
mpc_horz_traj = out.mpc_horz_traj.data;

% 1. Squeeze out any 3D singleton dimensions
if ndims(mpc_horz_traj) == 3, mpc_horz_traj = squeeze(mpc_horz_traj); end

% 2. Transpose matrices if they are oriented as [States x Time]
if size(mpc_horz_traj, 1) < size(mpc_horz_traj, 2) && size(mpc_horz_traj, 2) == N_t
    mpc_horz_traj = mpc_horz_traj';
end


required_road_len = length(sim_t) + Np;

if length(rho) < required_road_len
    % Pad the road curvature profile with zeros (straight line) for the remainder
    rho_padded = [rho; zeros(required_road_len - length(rho), 1)];
else
    rho_padded = rho;
end

road_len = length(rho_padded);
road_coords = zeros(road_len, 3);

% Put road curve into global coords for centerline
for i = 1:(road_len-1)
    road_coords(i+1, 3) = road_coords(i, 3) + Vx * rho_padded(i) * dt; % integrate with psi_dot
    road_coords(i+1, 1) = road_coords(i, 1) + Vx * cos(road_coords(i, 3)) * dt;
    road_coords(i+1, 2) = road_coords(i, 2) + Vx * sin(road_coords(i, 3)) * dt;
end

% Extract Coordinates
X_road = road_coords(:, 1);
Y_road = road_coords(:, 2);
theta_road = road_coords(:, 3);

% Global Coords
global_X_true = zeros(length(sim_t), 1);
global_Y_true = zeros(length(sim_t), 1);
global_X_hat  = zeros(length(sim_t), 1);
global_Y_hat  = zeros(length(sim_t), 1);

% Rotate true and estimated states into global frame
for k = 1:length(sim_t)
    th = theta_road(k);
    % Use Rotation Matrix
    R_matrix = [cos(th), -sin(th); 
                sin(th),  cos(th)];
    
    % Rotate True Car Position 
    pos_true = [X_road(k); Y_road(k)] + R_matrix * [0; x_true_vec(k, 1)];
    global_X_true(k) = pos_true(1);
    global_Y_true(k) = pos_true(2);
    
    % Rotate KF Estimated Position
    pos_hat = [X_road(k); Y_road(k)] + R_matrix * [0; x_hat_vec(k, 1)];
    global_X_hat(k) = pos_hat(1);
    global_Y_hat(k) = pos_hat(2);
end

% Figure
figure('Name', 'Simulink Closed-Loop S-Curve Performance', 'NumberTitle', 'off', 'Position', [100, 100, 1100, 550]);
subplot(3, 1, [1, 2]); hold on; grid on; axis equal;

% Draw Lane Boundaries
lane_width = 3.6;
X_left  = X_road - (lane_width/2) * sin(theta_road);
Y_left  = Y_road + (lane_width/2) * cos(theta_road);
X_right = X_road + (lane_width/2) * sin(theta_road);
Y_right = Y_road - (lane_width/2) * cos(theta_road);

plot(X_left, Y_left, 'k-', 'LineWidth', 2);
plot(X_right, Y_right, 'k-', 'LineWidth', 2);
plot(X_road, Y_road, 'r--', 'LineWidth', 1);

% Create persistent animation handles
hCarTrue   = plot(0, 0, 'Square', 'MarkerSize', 14, 'MarkerFaceColor', 'k', 'MarkerEdgeColor', 'k');
hCarEst    = plot(0, 0, 'o', 'MarkerSize', 8, 'MarkerFaceColor', 'r', 'MarkerEdgeColor', 'k');
hTruePath  = plot(NaN, NaN, 'b-', 'LineWidth', 1.5);
hHorizonTail = plot(NaN, NaN, 'g-o', 'LineWidth', 1.5, 'MarkerSize', 4, 'MarkerFaceColor', 'g');

title('Post-Processed Simulink Loop with MPC Prediction Horizon');
xlabel('Global Position X [meters]'); ylabel('Global Position Y [meters]');
legend([hCarTrue, hCarEst, hHorizonTail], {'True Physical Car', 'KF State Estimate', 'MPC Predicted Path'}, 'Location', 'northwest');

% Steering Subplot
subplot(3, 1, 3); hold on; grid on;
% Initialize steering line as empty (NaN) so it draws dynamically
hSteerLine = stairs(NaN, NaN, 'k', 'LineWidth', 1.5);
hSteerIndicator = stairs(0, 0, 'ro', 'MarkerFaceColor', 'r');
xlabel('Time [seconds]'); ylabel('Steering Input \delta [deg]');
ylim([-25, 25]); xlim([0, sim_t(end)]);


%% 5. Play Dynamic Animation Loop
for k = 1:length(sim_t)-1
    % Get current state mpc horizon trajectory (in error frame)
    current_Y_mpc = mpc_horz_traj(k, :);
    
    pred_X = zeros(Np, 1);
    pred_Y = zeros(Np, 1);
    
    for p = 1:Np
        % Get road index for the future point (bound it to prevent indexing errors)
        idx_future = min(k + p, length(X_road)); 
        
        % Extract predicted e1
        e1_pred = current_Y_mpc((p-1)*4 + 1); 
        
        % Compute mpc horizon path in global frame w/ Rotation Matrix
        th_future = theta_road(idx_future);
        R_matrix_future = [cos(th_future), -sin(th_future); 
                           sin(th_future),  cos(th_future)];
                       
        pos_pred = [X_road(idx_future); Y_road(idx_future)] + R_matrix_future * [0; e1_pred];
        
        pred_X(p) = pos_pred(1);
        pred_Y(p) = pos_pred(2);
    end
    
    % Update Animation
    subplot(3, 1, [1, 2]);
    set(hCarTrue, 'XData', global_X_true(k), 'YData', global_Y_true(k));
    set(hCarEst,  'XData', global_X_hat(k),  'YData', global_Y_hat(k));
    set(hTruePath, 'XData', global_X_true(1:k), 'YData', global_Y_true(1:k));
    set(hHorizonTail, 'XData', pred_X, 'YData', pred_Y);
    
    % Follow bike view
    xlim([global_X_true(k) - 20, global_X_true(k) + 40]);
    ylim([global_Y_true(k) - 10, global_Y_true(k) + 20]);
    
    % Update steering indicator
    subplot(3, 1, 3);
    set(hSteerLine, 'XData', sim_t(1:k), 'YData', rad2deg(u_optimal(1:k)));
    set(hSteerIndicator, 'XData', sim_t(k), 'YData', rad2deg(u_optimal(k)));
    
    drawnow;
end
