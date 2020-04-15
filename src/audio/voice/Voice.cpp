#include "Voice.h"
#include "audio/filter/HighpassFilter.h"
#include "audio/filter/LowpassFilter.h"
#include "audio/filter/BandpassFilter.h"


#include <iostream>

Voice::Voice( std::shared_ptr<IOscillatorFunction> pOscillator1
            , std::shared_ptr<IOscillatorFunction> pOscillator2
            , IEnvelope* pEnvelope
            , std::shared_ptr<IFilter> pFilter
            , std::shared_ptr<modulation::IModulator> pModulator
            , std::shared_ptr<IEnvelope> pGlobalEnvelope)
: m_pEnvelope(pEnvelope)
, m_pGlobalEnvelope(pGlobalEnvelope)
, m_pFilter(pFilter)
, m_fFrequency(0.0)
, m_fMix(0.5)
, m_pOscillator1(pOscillator1)
, m_pOscillator2(pOscillator2)
, m_bActive(false)
{   
    modulation::ModulationValue cutOff(0.01, 0.99, 0.99);
    m_pFilterCutOff = std::make_shared<modulation::ModulationValue>(cutOff);
    m_pFilterCutOff->setModulator(pModulator);
    m_pFilterCutOff->setEnvelopeModulator(pGlobalEnvelope);

    modulation::ModulationValue resonance(0.01, 0.99, 0.01);
    m_pFilterResonance = std::make_shared<modulation::ModulationValue>(resonance);
    m_pFilterResonance->setModulator(pModulator);
    m_pFilterResonance->setEnvelopeModulator(pGlobalEnvelope);
}

Voice::~Voice()
{

}

void Voice::noteOn(float fFrequency, float fTime)
{
    m_bActive = true;
    m_fFrequency = fFrequency;
    m_pEnvelope->noteOn(fTime);
    m_pGlobalEnvelope->noteOn(fTime);
    m_pFilter->triggerOn();
}

void Voice::noteOff(float fTime)
{   
    m_pEnvelope->noteOff(fTime);
    m_pGlobalEnvelope->noteOff(fTime);
    m_pFilter->triggerOff();
}

float Voice::process(float fTime)
{
    float osc1 = m_pOscillator1->calculate(m_fFrequency, fTime);
    float osc2 = m_pOscillator2->calculate(m_fFrequency, fTime);
    float amp = m_pEnvelope->getAmplitude(fTime);
    
    m_pFilter->setCutoffFrequency(m_pFilterCutOff->getModulatedValue(fTime));
    m_pFilter->setResonance(m_pFilterResonance->getModulatedValue(fTime));
    float filtered = m_pFilter->process( amp * (((1.0 - m_fMix) * osc1 + m_fMix * osc2)));
    
    if ((m_pEnvelope->isNoteOff() && m_pEnvelope->getCurrentAmplitude() == 0.0))
    {
        m_bActive = false;
    }
    
    return filtered;
}

void Voice::reset()
{
    m_pEnvelope->reset();
    m_pGlobalEnvelope->reset();
    m_pFilter->reset();
}

bool Voice::isActive()
{
    return m_bActive;
}

void Voice::setActive()
{
    m_bActive = true;
}

/******************************************************************************
    Setters and Getters
******************************************************************************/

float Voice::getFrequency()
{
    return m_fFrequency;
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

std::shared_ptr<IEnvelope> Voice::getGlobalEnvelope()
{
    return m_pGlobalEnvelope;
}
    

std::shared_ptr<IFilter> Voice::getFilter()
{
    return m_pFilter;
}

void Voice::setFilter(FilterType type)
{
    switch (type)
    {
        case FilterType::LOWPASS:
            m_pFilter = std::make_shared<LowpassFilter>();
        break;
        case FilterType::HIGHPASS:
            m_pFilter = std::make_shared<HighpassFilter>();
        break;
        case FilterType::BANDPASS:
            m_pFilter = std::make_shared<BandpassFilter>();
        break;
    }
}

void Voice::setOscillationMix(float fMix)
{
    m_fMix = fMix;
}

std::shared_ptr<modulation::ModulationValue> Voice::getFilterCutOff()
{
    return m_pFilterCutOff;
}

std::shared_ptr<modulation::ModulationValue> Voice::getFilterResonance()
{
    return m_pFilterResonance;
}