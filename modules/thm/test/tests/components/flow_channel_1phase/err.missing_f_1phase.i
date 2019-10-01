[GlobalParams]
  gravity_vector = '0 0 0'

  initial_vel = 0
  initial_p = 1e5
  initial_T = 300

  closures = simple

  spatial_discretization = RDG
  rdg_slope_reconstruction = none
[]

[FluidProperties]
  [./water]
    type = StiffenedGasFluidProperties
    gamma = 2.35
    cv = 1816.0
    q = -1.167e6
    p_inf = 1.0e9
    q_prime = 0
  [../]
[]

[Components]
  [./pipe]
    type = FlowChannel1Phase
    fp = water
    position = '0 0 0'
    orientation = '1 0 0'
    A = 1.
    length = 1
    n_elems = 10
  [../]

  [./inlet]
    type = InletStagnationPressureTemperature1Phase
    input = 'pipe:in'
    p0 = 10
    T0 = 10
  [../]

  [./outlet]
    type = Outlet1Phase
    input = 'pipe:out'
    p = 10
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

  dt = 1e-4
  dtmin = 1.e-7

  solve_type = 'PJFNK'
  nl_rel_tol = 1e-9
  nl_abs_tol = 1e-8
  nl_max_its = 10

  l_tol = 1e-8
  l_max_its = 100

  start_time = 0.0
  num_steps = 10

  [./Quadrature]
    type = GAUSS
    order = SECOND
  [../]
[]

[Outputs]
  exodus = true
[]
