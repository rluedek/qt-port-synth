#ifndef IFILTER_H
#define IFILTER_H

class IFilter
{
public: 
    virtual void triggerOn() = 0;
    virtual void triggerOff() = 0;

    virtual double process(double inputValue) = 0;

    virtual void setCutoffFrequency(double frequency) = 0;
    virtual void setResonance(double resonance) = 0;
    virtual double getFeedbackAmount() = 0;
};

#endif