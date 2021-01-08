//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "FVFluxBC.h"

class Function;

class INSFVNoSlipWallBC : public FVFluxBC
{
public:
  static InputParameters validParams();
  INSFVNoSlipWallBC(const InputParameters & params);
  Real boundaryValue(const FaceInfo & fi) const;

protected:
  ADReal computeQpResidual() override;

  /// x-velocity on the FaceInfo elem
  const ADVariableValue & _u_elem;
  /// y-velocity on the FaceInfo elem
  const ADVariableValue & _v_elem;
  /// z-velocity on the FaceInfo elem
  const ADVariableValue & _w_elem;

  /// x-velocity on the FaceInfo neighbor
  const ADVariableValue & _u_neighbor;
  /// y-velocity on the FaceInfo neighbor
  const ADVariableValue & _v_neighbor;
  /// z-velocity on the FaceInfo neighbor
  const ADVariableValue & _w_neighbor;

  /// What component of the velocity this object is acting on
  const unsigned int _comp;

  /// The dynamic viscosity on the FaceInfo elem
  const ADMaterialProperty<Real> & _mu_elem;
  /// The dynamic viscosity on the FaceInfo neighbor
  const ADMaterialProperty<Real> & _mu_neighbor;

  /// The mesh dimension
  const unsigned int _dim;

  /// The wall velocity in the x-direction
  const Function & _u_wall;
  /// The wall velocity in the y-direction
  const Function & _v_wall;
  /// The wall velocity in the z-direction
  const Function & _w_wall;
};
