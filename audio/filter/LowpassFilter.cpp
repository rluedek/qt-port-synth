#include "LowpassFilter.h"

//ctor
LowpassFilter::LowpassFilter()
: m_dCutoffFrequency(0.999)
, m_dBuf0(0.0)
, m_dBuf1(0.0)
, m_dBuf2(0.0)
, m_dResonance(0.0)
, m_bNoteOn(false)
{
  calculateFeedbackAmount();
}

//dtor
LowpassFilter::~LowpassFilter()
{

}

void LowpassFilter::triggerOn()
{
  m_bNoteOn = true;
}

void LowpassFilter::triggerOff()
{
  // reset buffers
  m_bNoteOn = false;
}

double LowpassFilter::process(double inputValue)
{
  m_dBuf0 += m_dCutoffFrequency *  (inputValue - m_dBuf0 + m_dFeedbackAmount * (m_dBuf0 - m_dBuf1));
  m_dBuf1 += m_dCutoffFrequency *  (m_dBuf0 - m_dBuf1);
  m_dBuf2 += m_dCutoffFrequency *  (m_dBuf1 - m_dBuf2);
  
  return m_dBuf2;
}

void LowpassFilter::setCutoffFrequency(double frequency)
{
  m_dCutoffFrequency = frequency;
  calculateFeedbackAmount();
}

void LowpassFilter::setResonance(double resonance)
{
  m_dResonance = resonance;
  calculateFeedbackAmount();
}

double LowpassFilter::getFeedbackAmount()
{
  return m_dFeedbackAmount;
}