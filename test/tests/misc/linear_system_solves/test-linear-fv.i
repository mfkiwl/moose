[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 4
[]

[Problem]
  linear_sys_names = 'u_sys'
  error_on_jacobian_nonzero_reallocation = true
  solve = false
[]

[Variables]
  [u]
    type = MooseLinearVariableFVReal
    linear_sys = 'u_sys'
    initial_condition = 1.0
  []
[]

[LinearFVKernels]
  [advection]
    type = LinearFVAdvectionKernel
    variable = u
    density = 1.3
    velocity = "0.5 0 0"
    advected_interp_method = average
  []
  [diffusion]
    type = LinearFVDiffusionKernel
    variable = u
    diffusion_coeff = 3.0
  []
  [reaction]
    type = LinearFVReactionKernel
    variable = u
    coeff = 5.0
  []
  [source]
    type = LinearFVSourceKernel
    variable = u
    source_density = 1.5
  []
[]

[LinearFVBCs]
  [left_dir]
    type = LinearFVDirichletBC
    variable = u
    boundary = "left"
    value = 1.0
  []
  [right_dir]
    type = LinearFVDirichletBC
    variable = u
    boundary = "right"
    value = 2.0
  []
[]

[Executioner]
  type = LinearPicardSteady
  linear_sys_to_solve = u_sys
[]

[Outputs]
  exodus = true
[]
