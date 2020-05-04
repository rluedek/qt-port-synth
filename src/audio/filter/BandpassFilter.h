/**
 * @copyright Copyright (c) 2020 Rico Luedeke
 * @author Rico Luedeke
 * @brief  This file is part of qt-port-synth (A baisc synthesizer using PortAudio and Qt5)
 * @date 2020-05-04
 * @see https://github.com/rluedek/qt-port-synth
 */

#ifndef BANDPASS_FILTER_H
#define BANDPASS_FILTER_H

#include "IFilter.h"

class BandpassFilter : public IFilter
{
public:
    //ctor
    BandpassFilter();
    //dtor
    ~BandpassFilter();

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