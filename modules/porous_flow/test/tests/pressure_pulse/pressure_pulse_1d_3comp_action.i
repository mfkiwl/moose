# Pressure pulse in 1D with 1 phase but 3 components (viscosity, relperm, etc are independent of mass-fractions) - transient
# This input file uses the PorousFlowFullySaturated Action.  For the non-Action version, see pressure_pulse_1d_3comp.i
[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 10
  xmin = 0
  xmax = 100
[]

[GlobalParams]
  PorousFlowDictator = dictator
[]

[Variables]
  [pp]
    initial_condition = 2E6
  []
  [massfrac0]
    initial_condition = 0.1
  []
  [massfrac1]
    initial_condition = 0.3
  []
[]

[PorousFlowFullySaturated]
  porepressure = pp
  mass_fraction_vars = 'massfrac0 massfrac1'
  gravity = '0 0 0'
  fp = simple_fluid
  stabilization = Full
[]

[Modules]
  [FluidProperties]
    [simple_fluid]
      type = SimpleFluidProperties
      bulk_modulus = 2e9
      density0 = 1000
      thermal_expansion = 0
      viscosity = 1e-3
    []
  []
[]

[Materials]
  [porosity]
    type = PorousFlowPorosityConst
    porosity = 0.1
  []
  [permeability]
    type = PorousFlowPermeabilityConst
    permeability = '1E-15 0 0 0 1E-15 0 0 0 1E-15'
  []
[]

[BCs]
  [left]
    type = DirichletBC
    boundary = left
    value = 3E6
    variable = pp
  []
[]

[Preconditioning]
  [andy]
    type = SMP
    full = true
  []
[]

[Executioner]
  type = Transient
  solve_type = Newton
  dt = 1E3
  end_time = 1E4
[]

[Postprocessors]
  [p000]
    type = PointValue
    variable = pp
    point = '0 0 0'
    execute_on = 'initial timestep_end'
  []
  [p010]
    type = PointValue
    variable = pp
    point = '10 0 0'
    execute_on = 'initial timestep_end'
  []
  [p020]
    type = PointValue
    variable = pp
    point = '20 0 0'
    execute_on = 'initial timestep_end'
  []
  [p030]
    type = PointValue
    variable = pp
    point = '30 0 0'
    execute_on = 'initial timestep_end'
  []
  [p040]
    type = PointValue
    variable = pp
    point = '40 0 0'
    execute_on = 'initial timestep_end'
  []
  [p050]
    type = PointValue
    variable = pp
    point = '50 0 0'
    execute_on = 'initial timestep_end'
  []
  [p060]
    type = PointValue
    variable = pp
    point = '60 0 0'
    execute_on = 'initial timestep_end'
  []
  [p070]
    type = PointValue
    variable = pp
    point = '70 0 0'
    execute_on = 'initial timestep_end'
  []
  [p080]
    type = PointValue
    variable = pp
    point = '80 0 0'
    execute_on = 'initial timestep_end'
  []
  [p090]
    type = PointValue
    variable = pp
    point = '90 0 0'
    execute_on = 'initial timestep_end'
  []
  [p100]
    type = PointValue
    variable = pp
    point = '100 0 0'
    execute_on = 'initial timestep_end'
  []
  [mf_0_010]
    type = PointValue
    variable = massfrac0
    point = '10 0 0'
    execute_on = 'timestep_end'
  []
  [mf_1_010]
    type = PointValue
    variable = massfrac1
    point = '10 0 0'
    execute_on = 'timestep_end'
  []
[]

[Outputs]
  file_base = pressure_pulse_1d_3comp
  print_linear_residuals = true
  csv = true
[]
