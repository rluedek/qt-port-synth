#include <iostream>
#include <memory>

#include "audio/voicemanager/VoiceManager.h"
#include "audio/envelope/Envelope.h"
#include "audio/filter/LowpassFilter.h"
#include "audio/voice/Voice.h"

VoiceManager::VoiceManager()
{
    m_pGain = std::make_shared<Param>(0.0,1.0, 0.2);

    m_pOscillatorMix = std::make_shared<Param>(0.0,1.0, 0.5);

    m_pEnvelopeAttackTime = std::make_shared<Param>(0.01, 0.99, 0.5);
    m_pEnvelopeReleaseTime = std::make_shared<Param>(0.01, 2.00, 0.5);
    m_pEnvelopeDecayTime = std::make_shared<Param>(0.01, 0.99, 0.5);
    m_pEnvelopeSustainAmplitude = std::make_shared<Param>(0.0,1.0,1.0);
    
    m_pFilterEnvelopeAttackTime = std::make_shared<Param>(0.01, 0.99, 0.5);
    m_pFilterEnvelopeReleaseTime = std::make_shared<Param>(0.01, 2.00, 0.5);
    m_pFilterEnvelopeDecayTime = std::make_shared<Param>(0.01, 0.99, 0.5);
    m_pFilterEnvelopeSustainAmplitude = std::make_shared<Param>(0.0,1.0,1.0);

    m_pLfoFrequency = std::make_shared<Param>(0.0, 20.0, 0.0);
    m_pLfoAmount = std::make_shared<Param>(0.0, 1.0, 0.0);

    m_pLfo = std::make_shared<Lfo>(m_pLfoFrequency, m_pLfoAmount);
    m_pLfo->setOscillator(std::make_shared<Sine>());

    createVoices();
}

IVoice* VoiceManager::findFreeVoice() 
{
    IVoice* freeVoice = nullptr;
    
    for (int i = 0; i < NumberOfVoices; i++)
    {   
        if (!voices[i]->isActive())
        {
            freeVoice = voices[i];
            break;
        }
    }
    
    return freeVoice;
}

void VoiceManager::noteOn(float fFrequency, float fTime)
{
    IVoice* pVoice = findFreeVoice();
    
    if (pVoice)
    {   
        pVoice->reset();
        pVoice->noteOn(fFrequency, fTime);
    }
}

void VoiceManager::noteOff(float fFrequency, float fTime)
{
    IVoice* pVoice = nullptr;
    
    for (int i = 0; i < NumberOfVoices; i++)
    {
        pVoice = voices[i];
        if (pVoice->isActive() && pVoice->getFrequency() == fFrequency)
        {
            pVoice->noteOff(fTime);
        }
    }
}

void VoiceManager::setGain(float gain)
{
    m_pGain->setValue(gain);
}

float VoiceManager::getSample(float fTime)
{   
    float value = 0.0;
    IVoice* pVoice = nullptr;
    m_pLfo->trigger(fTime);
    for (int i = 0; i < NumberOfVoices; i++)
    {   
        pVoice = voices[i];
        if (pVoice->isActive())
        {
            value += pVoice->process(fTime);
        }
    }

    return value * m_pGain->getValue();
}

void VoiceManager::createVoices()
{
    for (int i = 0; i < NumberOfVoices; i++)
    {
        std::shared_ptr<IOscillatorFunction> osc1 = std::make_shared<Sine>();
        std::shared_ptr<IOscillatorFunction> osc2 = std::make_shared<Square>();
        std::shared_ptr<IFilter> filter = std::make_shared<LowpassFilter>();

        std::shared_ptr<IEnvelope> pAmpEnvelope = std::make_shared<Envelope>(m_pEnvelopeAttackTime
                                                                    , m_pEnvelopeDecayTime
                                                                    , m_pEnvelopeReleaseTime
                                                                    , m_pEnvelopeSustainAmplitude);
        
        std::shared_ptr<IEnvelope> pFilterEnvelope = std::make_shared<Envelope>(m_pFilterEnvelopeAttackTime
                                                                    , m_pFilterEnvelopeDecayTime
                                                                    , m_pFilterEnvelopeReleaseTime
                                                                    , m_pFilterEnvelopeSustainAmplitude);

        IVoice* voice = new Voice(osc1, osc2, filter, m_pLfo, pFilterEnvelope, pAmpEnvelope);

        voices[i] = voice;
    }
}

void VoiceManager::setOscillator1(std::shared_ptr<IOscillatorFunction> func)
{
    for (int i = 0; i < NumberOfVoices; i++)
    {
        IVoice* pVoice = voices[i];

        if(pVoice)
        {
            pVoice->setOscillator1(func);
        }
    }
}

void VoiceManager::setOscillator2(std::shared_ptr<IOscillatorFunction> func)
{
    for (int i = 0; i < NumberOfVoices; i++)
    {
        IVoice* pVoice = voices[i];
        
        if(pVoice)
        {
            pVoice->setOscillator2(func);
        }
    }
}

void VoiceManager::setEnvelopeAttackTime(int dAttackTime)
{
    m_pEnvelopeAttackTime->setValue(dAttackTime / 1000.0);
}

void VoiceManager::setEnvelopeReleaseTime(int dReleaseTime)
{
    m_pEnvelopeReleaseTime->setValue(dReleaseTime / 1000.0);
}

void VoiceManager::setEnvelopeDecayTime(int dDecayTime)
{
    m_pEnvelopeDecayTime->setValue(dDecayTime / 1000.0);
}

void VoiceManager::setEnvelopeSustainAmplitude(int dSustainAmplitude)
{
    m_pEnvelopeSustainAmplitude->setValue(dSustainAmplitude / 1000.0);
}

void VoiceManager::setFilter(FilterType type)
{
    for (int i = 0; i < NumberOfVoices; i++)
    {
        IVoice* pVoice = voices[i];
        
        if(pVoice)
        {
            pVoice->setFilter(type);
        }
    }
}

void VoiceManager::setCutOffFrequency(int frequency)
{
    for (int i = 0; i < NumberOfVoices; i++)
    {
        IVoice* pVoice = voices[i];
        
        if(pVoice)
        {
            pVoice->getFilterCutOff()->setValue(frequency / 1000.0);
        }
    }
}

void VoiceManager::setResonance(int resonance)
{
    for (int i = 0; i < NumberOfVoices; i++)
    {
        IVoice* pVoice = voices[i];
        
        if(pVoice)
        {   
            pVoice->getFilterResonance()->setValue(resonance / 1000.0);
        }
    }
}

void VoiceManager::setOscillatorMix(int mix)
{
    for (int i = 0; i < NumberOfVoices; i++)
    {
        IVoice* pVoice = voices[i];
        
        if(pVoice)
        {   
            pVoice->setOscillationMix(mix / 1000.0);
        }
    }
}

//LFO
void VoiceManager::setLfo(std::shared_ptr<Lfo> pLfo)
{
    m_pLfo = pLfo;
}

void VoiceManager::setLfoFrequency(int frequency)
{
    m_pLfoFrequency->setValue(frequency / 1000.0);
}

void VoiceManager::setLfoAmount(int amount)
{
    m_pLfoAmount->setValue(amount / 1000.0);
}

void VoiceManager::setLfoOscillator(std::shared_ptr<IOscillatorFunction> func)
{
    m_pLfo->setOscillator(func);
}

void VoiceManager::setGlobalEnvelopeAttackTime(int dAttackTime)
{
    m_pFilterEnvelopeAttackTime->setValue(dAttackTime / 1000.0);
}

void VoiceManager::setGlobalEnvelopeReleaseTime(int dReleaseTime)
{
    m_pFilterEnvelopeReleaseTime->setValue(dReleaseTime / 1000.0);
}

void VoiceManager::setGlobalEnvelopeDecayTime(int dDecayTime)
{
    m_pFilterEnvelopeDecayTime->setValue(dDecayTime / 1000.0);
}

void VoiceManager::setGlobalEnvelopeSustainAmplitude(int dSustainAmplitude)
{
    m_pFilterEnvelopeSustainAmplitude->setValue(dSustainAmplitude / 1000.0);
}
