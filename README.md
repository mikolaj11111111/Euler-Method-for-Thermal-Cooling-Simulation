# Euler Method for Thermal Cooling Simulation

## Description
Solves differential equation for sphere cooling using Euler's method. Models thermal radiation according to Stefan-Boltzmann law and analyzes numerical accuracy for different step sizes.

## Features
- **Euler's Method** - First-order numerical ODE solver
- **Stefan-Boltzmann Law** - Models thermal radiation: dT/dt = -α·T⁴
- **Step Size Analysis** - Compares accuracy for h = {10, 1, 0.1, 0.01, 0.001}
- **Error Quantification** - Mean square error calculation
- **Result Visualization** - Tabular output with selected time points

## Mathematical Background
- **Differential Equation**: dT/dt = -α·T⁴
- **Euler's Formula**: T_{n+1} = T_n + h·f(t_n, T_n)
- **Stefan-Boltzmann**: Thermal radiation proportional to T⁴
- **Convergence**: Smaller step size → higher accuracy

## Physical Parameters
- **Initial Temperature**: T₀ = 2379 K (hot sphere)
- **Cooling Coefficient**: α = 9×10⁻¹² 
- **Time Domain**: [0, 100] seconds
- **Process**: Radiative cooling to ambient temperature

## Usage
Program automatically tests multiple step sizes and compares cooling curves, demonstrating trade-off between computational cost and numerical accuracy.
