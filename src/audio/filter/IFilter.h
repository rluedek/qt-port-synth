/**
 * @copyright Copyright (c) 2020 Rico Luedeke
 * @author Rico Luedeke
 * @brief  This file is part of qt-port-synth (A baisc synthesizer using PortAudio and Qt5)
 * @date 2020-05-04
 * @see https://github.com/rluedek/qt-port-synth
 */

#ifndef IFILTER_H
#define IFILTER_H

class IFilter
{

public: 
    virtual void triggerOn() = 0;
    virtual void triggerOff() = 0;

    virtual float process(float fInputValue) = 0;
    virtual void reset() = 0;


    virtual void setCutoffFrequency(float fFrequency) = 0;
    virtual void setResonance(float fResonance) = 0;
    virtual float getFeedbackAmount() = 0;
};

#endif