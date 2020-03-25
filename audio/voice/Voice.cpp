#include "Voice.h"

Voice::Voice(std::shared_ptr<IOscillatorFunction> pOscillator1
            , std::shared_ptr<IOscillatorFunction> pOscillator2
            , IEnvelope* pEnvelope
            , std::shared_ptr<IFilter> pFilter
            , std::shared_ptr<modulation::IModulator> pModulator)
: m_pEnvelope(pEnvelope)
, m_pFilter(pFilter)
, m_dFrequency(0.0)
, m_pOscillator1(pOscillator1)
, m_pOscillator2(pOscillator2)
{   
    modulation::ModulationValue cutOff(0.01, 0.99);
    m_pFilterCutOff = std::make_shared<modulation::ModulationValue>(cutOff);
    m_pFilterCutOff->setModulator(pModulator);

    modulation::ModulationValue resonance(0.01, 0.99);
    m_pFilterResonance = std::make_shared<modulation::ModulationValue>(resonance);
    m_pFilterResonance->setModulator(pModulator);
}

Voice::~Voice()
{

}

void Voice::noteOn(double dFrequency, double dTime)
{
    m_dFrequency = dFrequency;
    m_pEnvelope->noteOn(dTime);
    m_pFilter->triggerOn();
}

void Voice::noteOff(double dTime)
{
    m_pEnvelope->noteOff(dTime);
    m_pFilter->triggerOff();
}

double Voice::process(double dTime)
{
    float osc1 = (float)m_pOscillator1->calculate(m_dFrequency, dTime);
    float osc2 = (float)m_pOscillator2->calculate(m_dFrequency, dTime);
    float amp = (float)m_pEnvelope->getAmplitude(dTime);
    m_pFilter->setCutoffFrequency(m_pFilterCutOff->getModulatedValue());
    m_pFilter->setResonance(m_pFilterResonance->getModulatedValue());
    float filtered = m_pFilter->process( amp * (osc1 + osc2));
                        
    return filtered;       
}

bool Voice::isActive()
{
    return (m_pEnvelope->getCurrentAmplitude() != 0.0);
}

/******************************************************************************
    Setters and Getters
******************************************************************************/

double Voice::getFrequency()
{
    return m_dFrequency;
}

std::shared_ptr<IOscillatorFunction> Voice::getOscillator1()
{
    return m_pOscillator1;
}

void Voice::setOscillator1(std::shared_ptr<IOscillatorFunction> pOscillator)
{
    m_pOscillator1 = pOscillator;
}
    
std::shared_ptr<IOscillatorFunction> Voice::getOscillator2()
{
    return m_pOscillator2;
}

void Voice::setOscillator2(std::shared_ptr<IOscillatorFunction> pOscillator)
{
    m_pOscillator2 = pOscillator;
}

IEnvelope* Voice::getEnvelope()
{
    return m_pEnvelope;
}

void Voice::setEnvelope(IEnvelope* pEnvelope)
{
    m_pEnvelope = pEnvelope;
}

std::shared_ptr<IFilter> Voice::getFilter()
{
    return m_pFilter;
}

void Voice::setFilter(std::shared_ptr<IFilter> pFilter)
{
    m_pFilter = pFilter;
}

std::shared_ptr<modulation::ModulationValue> Voice::getFilterCutOff()
{
    return m_pFilterCutOff;
}

std::shared_ptr<modulation::ModulationValue> Voice::getFilterResonance()
{
    return m_pFilterResonance;
}