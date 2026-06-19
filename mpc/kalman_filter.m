function [x_hat_p, P_hat_p, K_kf] = kalman_filter(x_hat, u, P_hat, rho, x_meas, Ad, Bd, Ed, H, Q_kf, R_kf)

% Measure only lateral and heading error (camera and IMU)

% Time Update
x_hat_m = Ad*x_hat + Bd*u + Ed*rho; % propogate states
P_hat_m = Ad*P_hat*Ad'+ Q_kf; % propogate covariance

% Measurement Innovation
innovation = x_meas - H*x_hat_m; % create residual between meas and dynamics
K_kf = P_hat_m*H'/(H*P_hat_m*H' + R_kf); % compute optimal Kalman gain

x_hat_p = x_hat_m + K_kf*innovation; % update estimated states
P_hat_p = (eye(size(Ad))-K_kf*H)*P_hat_m; % update covariance
P_hat_p = (P_hat_p + P_hat_p') / 2; % force symmetry for covariance

end