/**
 * @copyright Copyright (c) 2020 Rico Luedeke
 * @author Rico Luedeke
 * @brief  This file is part of qt-port-synth (A baisc synthesizer using PortAudio and Qt5)
 * @date 2020-05-04
 * @see https://github.com/rluedek/qt-port-synth
 */

#ifndef IVOICE_H
#define IVOICE_H

#include "audio/IOscillatorFunction.h"
#include "audio/envelope/IEnvelope.h"
#include "audio/filter/IFilter.h"

#include "audio/modulation/ModulationValue.h"
#include "audio/filter/FilterTypes.h"


#include <memory>

class IVoice
{
public:

    virtual void noteOn(float fFrequency, float fTime) = 0;

    virtual void noteOff(float fTime) = 0;

    virtual float process(float fTime) = 0;

    virtual void reset() = 0;

    virtual bool isActive() = 0;
    virtual void setActive() = 0;

    virtual float getFrequency() = 0;

    virtual std::shared_ptr<IOscillatorFunction> getOscillator1() = 0;
    virtual void setOscillator1(std::shared_ptr<IOscillatorFunction> func) = 0;
     
    virtual std::shared_ptr<IOscillatorFunction> getOscillator2() = 0;
    virtual void setOscillator2(std::shared_ptr<IOscillatorFunction> func) = 0;

    virtual std::shared_ptr<IEnvelope> getAmpEnvelope() = 0;

    virtual std::shared_ptr<IEnvelope> getFilterEnvelope() = 0;
    
    virtual std::shared_ptr<IFilter> getFilter() = 0;
    virtual void setFilter(FilterType type) = 0;

    virtual void setOscillationMix(float fMix) = 0;

    virtual std::shared_ptr<modulation::ModulationValue> getFilterCutOff() = 0;
    virtual std::shared_ptr<modulation::ModulationValue> getFilterResonance() = 0;

};

#endif