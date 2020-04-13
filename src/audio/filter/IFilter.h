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