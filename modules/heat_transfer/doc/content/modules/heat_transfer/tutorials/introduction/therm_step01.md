# Step 1 - First steps

Let's get started with a minimal input file.

!listing modules/heat_transfer/tutorials/introduction/therm_step01.i

## Input file

### `Mesh`

We create a simple regular orthogonal mesh block using the
[`GeneratedMeshGenerator`](GeneratedMeshGenerator.md). All subblocks under
`[Mesh]` are the so called [*MeshGenerators*](meshgenerators/MeshGenerator.md).
They can be chained together and MOOSE provides a multitude of generators to
create and modify meshes. A commonly used MeshGenerator is the
[`FileMeshGenerator`](FileMeshGenerator.md), it is used to load a mesh file
generated by third party software like Cubit or Gmsh (or sometimes even meshes
generated by MOOSE). MOOSE provides a shorthand for the `FileMeshGenerator`
through the [!param](/Mesh/FileMesh/file) parameter inside `[Mesh]`, e.g.

```
[Mesh]
  file = pressure_vessel.e
[]
```

MOOSE supports a [variety of mesh file formats](FileMeshGenerator.md); most
commonly used is the Exodus format.

### `Variables`

This top-level block is used to define the variables that are being solved
in this model. These variables define spatially varying fields that are defined
using a set of degrees of freedom and finite element interpolation functions.
MOOSE provides access to a wide variety of methods for defining these variables.
The default `LAGRANGE` variable type is defined at finite element nodes, and
interpolated from the values of the connected nodes within an element.

In the case of this model, a single variable is solved. This variable, named `T`,
is the temperature. The name of the variable is defined by the name in the opening
brackets of the block (`[T]`). There is no content in the block in this case because
only the default parameters are used.

!listing modules/heat_transfer/tutorials/introduction/therm_step01.i block=Variables

### `Kernels`

This top-level block is used to define the kernels that provide volume integrals
in the partial differential equation being solved. Generally, a separate `Kernel`
is used to define each term in a partial differential equation. The full heat equation
is generally expressed with multiple terms, as described in the Heat Transfer module
[introduction](modules/heat_transfer/index.md). However, for this simple example, we are only
including the conduction term, so the equation being solve takes the form:

\begin{equation}\label{eq:heat_transfer_equation}
  0 = \nabla k(t,\vec{x}) \nabla T ~\text{for}~\vec{x} \in \Omega,
\end{equation}

where $T$ is the temperature, $t$ is time, $\vec{x}$ is the vector of spatial coordinates,
and $\Omega$ is the solution domain. Later problems in this series will add the
additional terms to the heat equation.

The single `[heat_transfer]' block nested in the `Kernels` block defines the conduction
term in the heat equation defined above. The `type = HeatConduction` parameter defines
the name of the Kernel object that provides that term, and the `variable = T` parameter
defines the variable that the kernel is operating on. There is only one variable in the case
of this model, but in a multiphysics simulation, individual kernels would be assigned
to operate on specific variables.

!listing modules/heat_transfer/tutorials/introduction/therm_step01.i block=Kernels

### `Materials`

The `Materials` block is used to define material properties, which are evaluated at
the finite element integration points. In general, these material properties can
have complex dependencies on the solution variables and other quantities computed
by the code, but in this case, a constant values is defined.

The `HeatConductionMaterial` is a model that provides basic properties used for
the terms in the heat equation. In this case, the only property needed is the thermal
conductivity, which is defined with a constant value.

!listing modules/heat_transfer/tutorials/introduction/therm_step01.i block=Materials

### `Executioner`

In the [`[Executioner]`](Executioner/index.md) block all parameters relevant to the solution of the current
problem are set. [`type = Transient`](Transient.md) selects a time-dependent simulation (as
opposed to [`type = Steady`](Steady.md)). We chose to run for five simulation steps; with a
timestep of `1`.

!listing modules/heat_transfer/tutorials/introduction/therm_step01.i block=Executioner

### `Outputs`

We use the `exodus = true` shorthand to setup an output object of type `Exodus` to write
an Exodus mesh and solution file to the disk. You can visualize these outputs using
[Paraview](https://www.paraview.org).

!listing modules/heat_transfer/tutorials/introduction/therm_step01.i block=Outputs

## Questions

### Units

A question that comes up often is "What units does MOOSE use?".

>  Look through the input file and try to identify places where units might be
>  relevant.

[Click here for the answer.](heat_transfer/tutorials/introduction/answer01a.md)

### Expected outcome

> Before you run this first input file take a moment to think about what you
> expect to happen.

[Click here for the answer.](heat_transfer/tutorials/introduction/answer01b.md)

Once you've answered the questions and run the first example it is time to move
on to a slightly more complex scenario in [Step 2](heat_transfer/tutorials/introduction/therm_step02.md).
