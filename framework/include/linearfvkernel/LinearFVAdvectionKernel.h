//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "LinearFVFluxKernel.h"

class LinearFVAdvectionKernel : public LinearFVFluxKernel
{
public:
  static InputParameters validParams();
  LinearFVAdvectionKernel(const InputParameters & params);

  virtual Real computeElemMatrixContribution() override;

  virtual Real computeNeighborMatrixContribution() override;

  virtual Real computeElemRightHandSideContribution() override;

  virtual Real computeNeighborRightHandSideContribution() override;

  virtual Real computeBoundaryMatrixContribution(const LinearFVBoundaryCondition * bc) override;

  virtual Real computeBoundaryRHSContribution(const LinearFVBoundaryCondition * bc) override;

protected:
  /// Constant advecting velocity vector
  const RealVectorValue _velocity;

  /// The interpolation method to use for the advected quantity
  Moose::FV::InterpMethod _advected_interp_method;
};
