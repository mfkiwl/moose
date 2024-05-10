//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

// MOOSE includes
#include "Action.h"

/**
 * Base class for components that are defined using an action
 */
class ComponentAction : public Action
{
public:
  /**
   * Class constructor
   */
  static InputParameters validParams();

  ComponentAction(const InputParameters & params);

  virtual void act() override final;

  /// Use this if registering a new task to the derived ComponentAction
  virtual void actOnAdditionalTasks(){};

protected:
  // The default implementation of these routines will do nothing as we do not expect all Components
  // to be defining an object of every type
  // These routines are to help define a strictly geometrical component
  virtual void addMeshGenerators() {}
  virtual void addPositionsObject() {}
  virtual void addUserObjects() {}

  // These routines can help define a component that also defines a Physics
  virtual void addNonlinearVariables() {}
};
