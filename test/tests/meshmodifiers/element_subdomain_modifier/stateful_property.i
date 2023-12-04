[Problem]
  solve = false
[]

[Mesh]
  [gen]
    type = GeneratedMeshGenerator
    dim = 2
    nx = 16
    ny = 16
  []
  [left]
    type = SubdomainBoundingBoxGenerator
    input = 'gen'
    block_id = 1
    block_name = 'left'
    bottom_left = '0 0 0'
    top_right = '0.25 1 1'
  []
  [right]
    type = SubdomainBoundingBoxGenerator
    input = 'left'
    block_id = 2
    block_name = 'right'
    bottom_left = '0.25 0 0'
    top_right = '1 1 1'
  []
[]

[MeshModifiers]
  [moving_circle]
    type = CoupledVarThresholdElementSubdomainModifier
    coupled_var = 'phi'
    criterion_type = 'BELOW'
    threshold = 0
    subdomain_id = 1
    execute_on = 'INITIAL TIMESTEP_BEGIN'
  []
[]

[AuxVariables]
  [phi]
    [AuxKernel]
      type = ParsedAux
      expression = '(x-t)^2+(y)^2-0.5^2'
      use_xyzt = true
      execute_on = 'INITIAL TIMESTEP_BEGIN'
    []
  []
[]

[Materials]
  [stateful]
    type = StatefulMaterial
    initial_diffusivity = 0.5
    multiplier = 2
    block = 'left'
    outputs = 'exodus'
  []
  [non_stateful]
    type = GenericConstantMaterial
    prop_names = 'diffusivity'
    prop_values = '-1'
    block = 'right'
    outputs = 'exodus'
  []
[]

[Executioner]
  type = Transient
  dt = 0.1
  num_steps = 3
[]

[Outputs]
  exodus = true
[]
