//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "nlohmann/json.h"
#include "AdvancedOutput.h"

class JSONOutput : public AdvancedOutput
{
public:
  static InputParameters validParams();
  JSONOutput(const InputParameters & parameters);

protected:
  virtual void output(const ExecFlagType & type) override;
  virtual void outputReporters() override;
  virtual void outputSystemInformation() override;
  virtual std::string filename() override;
  const ReporterData & _reporter_data;

private:
  /// The root JSON node for output
  nlohmann::json _json;

  /// True when distributed data exists for output
  bool _has_distributed = false;
};
