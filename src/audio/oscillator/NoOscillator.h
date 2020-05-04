/**
 * @copyright Copyright (c) 2020 Rico Luedeke
 * @author Rico Luedeke
 * @brief  This file is part of qt-port-synth (A baisc synthesizer using PortAudio and Qt5)
 * @date 2020-05-04
 * @see https://github.com/rluedek/qt-port-synth
 */

#ifndef NO_OSCILLATOR_H
#define NO_OSCILLATOR_H

#include "audio/IOscillatorFunction.h"

class NoOscillator : public IOscillatorFunction
{
   float calculate(float& fTime, float fFrequency) override
   {
       return 0.0;
   }
};

#endif