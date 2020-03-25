#ifndef ILFO_H
#define ILFO_H

#include "audio/IOscillatorFunction.h"

#include <memory>

class ILfo
{
public:
    virtual void setFrequency(double dFrequency) = 0;
    virtual void setAmount(double dAmount) = 0;
    virtual void setOscillator(std::shared_ptr<IOscillatorFunction> pOscillator) = 0;

    virtual void trigger(double dTime) = 0;
};
#endif
