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