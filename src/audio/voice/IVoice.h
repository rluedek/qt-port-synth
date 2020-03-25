#ifndef IVOICE_H
#define IVOICE_H

#include "audio/IOscillatorFunction.h"
#include "audio/envelope/IEnvelope.h"
#include "audio/filter/IFilter.h"

#include "audio/modulation/ModulationValue.h"

#include <memory>

class IVoice
{
public:

    virtual void noteOn(double dFrequency, double dTime) = 0;

    virtual void noteOff(double dTime) = 0;

    virtual double process(double dTime) = 0;

    virtual bool isActive() = 0;

    virtual double getFrequency() = 0;

    virtual std::shared_ptr<IOscillatorFunction> getOscillator1() = 0;
    virtual void setOscillator1(std::shared_ptr<IOscillatorFunction> func) = 0;
     
    virtual std::shared_ptr<IOscillatorFunction> getOscillator2() = 0;
    virtual void setOscillator2(std::shared_ptr<IOscillatorFunction> func) = 0;

    virtual IEnvelope* getEnvelope() = 0;
    virtual void setEnvelope(IEnvelope* pEnvelope) = 0;
    
    virtual std::shared_ptr<IFilter> getFilter() = 0;
    virtual void setFilter(std::shared_ptr<IFilter> pFilter) = 0;

    virtual std::shared_ptr<modulation::ModulationValue> getFilterCutOff() = 0;
    virtual std::shared_ptr<modulation::ModulationValue> getFilterResonance() = 0;

};

#endif