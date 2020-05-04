/**
 * @copyright Copyright (c) 2020 Rico Luedeke
 * @author Rico Luedeke
 * @brief  This file is part of qt-port-synth (A baisc synthesizer using PortAudio and Qt5)
 * @date 2020-05-04
 * @see https://github.com/rluedek/qt-port-synth
 */

#ifndef ILFO_H
#define ILFO_H

#include "audio/IOscillatorFunction.h"

#include <memory>

class ILfo
{
public:
    virtual void setOscillator(std::shared_ptr<IOscillatorFunction> pOscillator) = 0;

    virtual void trigger(float fTime) = 0;
    
    virtual float getModulationAmount() = 0;

};
#endif