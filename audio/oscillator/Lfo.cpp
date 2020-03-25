#include "audio/oscillator/Lfo.h"

#include "qdebug.h"

Lfo::Lfo()
: m_dFrequency(20.0)
, m_dAmount(0.3)
, m_dModulationAmount(0.0)
{

}

void Lfo::setFrequency(double dFrequency)
{
    m_dFrequency = dFrequency;
}

void Lfo::setAmount(double dAmount)
{
    m_dAmount = dAmount;
}

void Lfo::setOscillator(std::shared_ptr<IOscillatorFunction> pOscillator)
{
    m_pOscillator = pOscillator;
}

void Lfo::trigger(double dTime)
{
    m_dModulationAmount = m_dAmount * (m_pOscillator.get()->calculate(dTime, m_dFrequency));
}

double Lfo::getModulationAmount()
{
    return m_dModulationAmount;
}