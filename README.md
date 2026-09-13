# MPC_Lane_Keeper

## Project Overview
Created a lane-keeping controller of a lateral bike model using a Kalman Filter (KF) and Model Predictive Control (MPC) for autonomous lane tracking in Simulink. Road curvature is fed as an input to the bike controller block as a measured distrubance, allowing for full state estimation from the noisy heading error states. The full-state estimate feeds into the MPC block to solve an optimal steering command over a 20-step prediction horizon, constrained to keep the actuator input within ±25 degrees.

## Block Diagram
A high-level block diagram of the model's structure is shown below.

<p align="center">
  <img src="results/MPC_Lane_Keeper_Block_Diagram.png" width="700">
</p>

## Simulink Model
The Simulink model is shown below, where the KF and MPC are combined into a single bike controller subsystem. The bike controller block is structured with MATLAB code generation (codegen) in mind for eventual deployment to embedded hardware such as a Teensy.

<p align="center">
  <img src="results/MPC_Lane_Keeper_Simulink.png" width="700">
</p>

## Closed Loop Simulation
The video below shows a closed-loop, lane tracking simulation. The black square represents the true vehicle position, the red dot represents the KF state estimate, and the green line shows the MPC prediction horizon at each time step. The lower plot shows the steering command, which remains within the ±25° actuator constraint.

https://github.com/user-attachments/assets/d0f66440-f11f-4f1f-9e1b-aff1d43e83b8
