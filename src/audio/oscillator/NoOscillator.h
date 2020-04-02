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