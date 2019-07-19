# Tests a junction between 2 flow channels of equal area and orientation. A
# sinusoidal density shape is advected to the right and should not be affected
# by the junction; the solution should be identical to the equivalent
# no-junction solution.

[GlobalParams]
  gravity_vector = '0 0 0'

  initial_p = 1e5
  initial_vel = 1

  A = 25

  f = 0

  fp = fp

  scaling_factor_1phase = '0.04 0.04 0.04e-5'

  spatial_discretization = RDG
  rdg_slope_reconstruction = none

  closures = simple
[]

[FluidProperties]
  [./fp]
    type = StiffenedGasFluidProperties
    gamma = 1.4
    cv = 725
    p_inf = 0
    q = 0
    q_prime = 0
  [../]
[]

[Functions]
  [./T0]
    type = CosineHumpFunction
    axis = x
    hump_center_position = 1
    hump_width = 0.5
    hump_begin_value = 250
    hump_center_value = 300
  [../]
[]

[Components]
  [./inlet]
    type = InletStagnationPressureTemperature1Phase
    input = 'pipe1:in'
    # Stagnation property with p = 1e5 Pa, T = 250 K, vel = 1 m/s
    p0 = 100000.68965687
    T0 = 250.00049261084
  [../]

  [./pipe1]
    type = FlowChannel1Phase

    position = '0 0 0'
    orientation = '1 0 0'
    length = 1

    initial_T = T0

    n_elems = 25
  [../]

  [./junction]
    type = VolumeJunction1Phase
    connections = 'pipe1:out pipe2:in'

    # NOTE: volume parameters are added via command-line arguments by tests file.
    position = '1.02 0 0'

    initial_T = T0
    initial_vel_x = 1
    initial_vel_y = 0
    initial_vel_z = 0

    scaling_factor_rhoV  = 1
    scaling_factor_rhouV = 1
    scaling_factor_rhovV = 1
    scaling_factor_rhowV = 1
    scaling_factor_rhoEV = 1e-5
  [../]

  [./pipe2]
    type = FlowChannel1Phase

    position = '1.04 0 0'
    orientation = '1 0 0'
    length = 0.96

    initial_T = T0

    n_elems = 24
  [../]

  [./outlet]
    type = Outlet1Phase
    input = 'pipe2:out'
    p = 1e5
  [../]
[]

[Preconditioning]
  [./pc]
    type = SMP
    full = true
  [../]
[]

[Executioner]
  type = Transient

  scheme = 'bdf2'
  start_time = 0
  dt = 0.01
  num_steps = 5
  abort_on_solve_fail = true

  solve_type = 'PJFNK'
  line_search = 'basic'
  nl_rel_tol = 0
  nl_abs_tol = 1e-6
  nl_max_its = 10

  l_tol = 1e-3
  l_max_its = 10

  [./Quadrature]
    type = GAUSS
    order = SECOND
  [../]
[]

[Postprocessors]
  [./junction_rho]
    type = ScalarVariable
    variable = junction:rhoV
    execute_on = 'initial timestep_end'
  [../]
  [./junction_rhou]
    type = ScalarVariable
    variable = junction:rhouV
    execute_on = 'initial timestep_end'
  [../]
  [./junction_rhoE]
    type = ScalarVariable
    variable = junction:rhoEV
    execute_on = 'initial timestep_end'
  [../]
[]

[Outputs]
  [./out]
    type = CSV
    execute_scalars_on = 'none'
    execute_on = 'initial timestep_end'
  [../]
[]
