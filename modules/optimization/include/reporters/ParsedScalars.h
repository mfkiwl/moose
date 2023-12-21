//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "ParsedReporterBase.h"

/**
 * Reporter containing operation between vectors from another Reporter
 */
class ParsedScalars : public ParsedReporterBase
{
public:
  static InputParameters validParams();

  ParsedScalars(const InputParameters & parameters);

  virtual void initialize() override {}
  virtual void execute() override {}
  virtual void finalize() override;

private:
  /// output vector
  Real & _output_reporter;

  std::vector<const Real *> _reporter_data;
};
