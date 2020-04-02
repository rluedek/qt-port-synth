#ifndef NO_FILTER_H
#define NO_FILTER_H

#include "IFilter.h"

class NoFilter : public IFilter
{
    void triggerOn() override
    {
        // do nothing
    }

    void triggerOff()override
    {
        // do nothing
    }

    float process(float fInputValue)
    {
        return fInputValue;
    }    
};

#endif