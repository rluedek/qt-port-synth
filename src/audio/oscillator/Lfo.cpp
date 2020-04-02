#include "audio/oscillator/Lfo.h"

Lfo::Lfo()
: m_fFrequency(20.0)
, m_fAmount(0.3)
, m_fModulationAmount(0.0)
{

}

void Lfo::setFrequency(float fFrequency)
{
    m_fFrequency = fFrequency;
}

void Lfo::setAmount(float fAmount)
{
    m_fAmount = fAmount;
}

void Lfo::setOscillator(std::shared_ptr<IOscillatorFunction> pOscillator)
{
    m_pOscillator = pOscillator;
}

void Lfo::trigger(float fTime)
{
    m_fModulationAmount = m_fAmount * (m_pOscillator.get()->calculate(fTime, m_fFrequency));
}

float Lfo::getModulationAmount()
{
    return m_fModulationAmount;
}