//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "SideSetsGeneratorBase.h"

/**
 * MeshGenerator for constructing side Sets from node sets
 */
class SideSetsFromNodeSetsGenerator : public SideSetsGeneratorBase
{
public:
  static InputParameters validParams();

  SideSetsFromNodeSetsGenerator(const InputParameters & parameters);

protected:
  std::unique_ptr<MeshBase> generate() override;
};
