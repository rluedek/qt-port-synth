#ifndef NO_OSCILLATOR_H
#define NO_OSCILLATOR_H

#include "audio/IOscillatorFunction.h"

class NoOscillator : public IOscillatorFunction
{
   double calculate(double& time, double frequency) override
   {
       return 0;
   }
};

#endif