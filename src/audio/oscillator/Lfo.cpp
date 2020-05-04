#include "audio/oscillator/Lfo.h"

Lfo::Lfo(std::shared_ptr<Param> pFrequency
        , std::shared_ptr<Param> pAmount)
: m_pFrequency(pFrequency)
, m_pAmount(pAmount)
, m_fModulationAmount(0.0)
{

}

void Lfo::setOscillator(std::shared_ptr<IOscillatorFunction> pOscillator)
{
    m_pOscillator = pOscillator;
}

void Lfo::trigger(float fTime)
{
    m_fModulationAmount = m_pAmount->getValue() * (m_pOscillator.get()->calculate(fTime, m_pFrequency->getValue()));
}

float Lfo::getModulationAmount()
{
    return m_fModulationAmount;
}