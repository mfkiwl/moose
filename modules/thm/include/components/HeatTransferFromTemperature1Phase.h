#ifndef HEATTRANSFERFROMTEMPERATURE1PHASE_H
#define HEATTRANSFERFROMTEMPERATURE1PHASE_H

#include "HeatTransfer1PhaseBase.h"

class HeatTransferFromTemperature1Phase;

template <>
InputParameters validParams<HeatTransferFromTemperature1Phase>();

/**
 * Base class for heat transfer connections from temperature for 1-phase flow
 */
class HeatTransferFromTemperature1Phase : public HeatTransfer1PhaseBase
{
public:
  HeatTransferFromTemperature1Phase(const InputParameters & parameters);

  virtual void addVariables() override;
  virtual void addMooseObjects() override;

  virtual bool isTemperatureType() const override;

protected:
  /**
   * Adds 1-phase heat transfer kernels
   */
  void addHeatTransferKernels();
};

#endif /* HEATTRANSFERFROMTEMPERATURE1PHASE_H */
