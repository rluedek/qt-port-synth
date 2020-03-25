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