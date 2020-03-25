#ifndef LOWPASS_FILTER_H
#define LOWPASS_FILTER_H

#include "IFilter.h"

class LowpassFilter : public IFilter
{
public:
    //ctor
    LowpassFilter();
    //dtor
    ~LowpassFilter();

    void triggerOn() override;
    void triggerOff() override;

    double process(double inputValue) override;

    void setCutoffFrequency(double frequency) override;
    void setResonance(double resonance) override;
    double getFeedbackAmount() override;

private:

    double m_dCutoffFrequency;
    double m_dBuf0;
    double m_dBuf1;
    double m_dBuf2;

    double m_dResonance;
    double m_dFeedbackAmount;

    bool m_bNoteOn;

    inline void calculateFeedbackAmount() { m_dFeedbackAmount = m_dResonance + m_dResonance/(1.0 - m_dCutoffFrequency); }
};

#endif //LOWPASS_FILTER_H