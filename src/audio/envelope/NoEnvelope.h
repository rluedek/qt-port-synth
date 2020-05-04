/**
 * @copyright Copyright (c) 2020 Rico Luedeke
 * @author Rico Luedeke
 * @brief  This file is part of qt-port-synth (A baisc synthesizer using PortAudio and Qt5)
 * @date 2020-05-04
 * @see https://github.com/rluedek/qt-port-synth
 */

#ifndef NO_ENVELOPE_H
#define NO_ENVELOPE_H

#include "IEnvelope.h"

class NoEnvelope : public IEnvelope
{
    void noteOn(double dTime) override
    {
        // do nothing
    }

    void noteOff(double dTime) override
    {
        // do nothing
    }
    
    double getAmplitude(double dTime) override
    {
        return 1.0;
    }
};

#endif