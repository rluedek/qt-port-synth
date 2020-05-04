/**
 * @copyright Copyright (c) 2020 Rico Luedeke
 * @author Rico Luedeke
 * @brief  This file is part of qt-port-synth (A baisc synthesizer using PortAudio and Qt5)
 * @date 2020-05-04
 * @see https://github.com/rluedek/qt-port-synth
 */

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