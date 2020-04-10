#ifndef HIGHPASS_FILTER_H
#define HIGHPASS_FILTER_H

#include "IFilter.h"

class HighpassFilter : public IFilter
{
public:
    //ctor
    HighpassFilter();
    //dtor
    ~HighpassFilter();

    void triggerOn() override;
    void triggerOff() override;

    float process(float fInputValue) override;
    void  reset() override;

    void setCutoffFrequency(float fFrequency) override;
    void setResonance(float fResonance) override;
    float getFeedbackAmount() override;

private:

    float m_fCutoffFrequency;
    float m_fBuf0;
    float m_fBuf1;
    float m_fBuf2;

    float m_fResonance;
    float m_fFeedbackAmount;

    bool m_bNoteOn;

    inline void calculateFeedbackAmount() { m_fFeedbackAmount = m_fResonance + m_fResonance/(1.0 - m_fCutoffFrequency); }
};

#endif