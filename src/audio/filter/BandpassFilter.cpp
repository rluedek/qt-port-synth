/**
 * @copyright Copyright (c) 2020 Rico Luedeke
 * @author Rico Luedeke
 * @brief  This file is part of qt-port-synth (A baisc synthesizer using PortAudio and Qt5)
 * @date 2020-05-04
 * @see https://github.com/rluedek/qt-port-synth
 */

#include "BandpassFilter.h"

//ctor
BandpassFilter::BandpassFilter()
: m_fCutoffFrequency(0.999)
, m_fBuf0(0.0)
, m_fBuf1(0.0)
, m_fBuf2(0.0)
, m_fResonance(0.0)
, m_bNoteOn(false)
{
  calculateFeedbackAmount();
}

//dtor
BandpassFilter::~BandpassFilter()
{

}

void BandpassFilter::triggerOn()
{
  m_bNoteOn = true;
}

void BandpassFilter::triggerOff()
{
  // reset buffers
  m_bNoteOn = false;
}

float BandpassFilter::process(float fInputValue)
{
  m_fBuf0 += m_fCutoffFrequency *  (fInputValue - m_fBuf0 + m_fFeedbackAmount * (m_fBuf0 - m_fBuf1));
  m_fBuf1 += m_fCutoffFrequency *  (m_fBuf0 - m_fBuf1);
  m_fBuf2 += m_fCutoffFrequency *  (m_fBuf1 - m_fBuf2);
  
  return m_fBuf0 - m_fBuf2;
}

void BandpassFilter::reset()
{
  m_fBuf0 = m_fBuf1 = m_fBuf2 = 0.0;
}

void BandpassFilter::setCutoffFrequency(float fFrequency)
{
  m_fCutoffFrequency = fFrequency;
  calculateFeedbackAmount();
}

void BandpassFilter::setResonance(float fResonance)
{
  m_fResonance = fResonance;
  calculateFeedbackAmount();
}

float BandpassFilter::getFeedbackAmount()
{
  return m_fFeedbackAmount;
}