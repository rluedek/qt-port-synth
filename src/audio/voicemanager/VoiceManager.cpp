#include "audio/voicemanager/VoiceManager.h"

#include <iostream>
#include <memory>

#include "audio/envelope/Envelope.h"
#include "audio/filter/LowpassFilter.h"
#include "audio/voice/Voice.h"


VoiceManager::VoiceManager()
{
    //create the global Lfo
    Lfo lfo;
    std::shared_ptr<IOscillatorFunction> lfoOsc = std::make_shared<Sine>();
    lfo.setOscillator(lfoOsc);
    m_pLfo = std::make_shared<Lfo>(lfo);

    Envelope envelope;
    m_pEnvelope = std::make_shared<Envelope>(envelope);

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
    m_pEnvelope->noteOn(fTime);

    if (pVoice)
    {   
        pVoice->reset();
        pVoice->noteOn(fFrequency, fTime);
    }
}

void VoiceManager::noteOff(float fFrequency, float fTime)
{
    IVoice* pVoice = nullptr;
    m_pEnvelope->noteOff(fTime);
    for (int i = 0; i < NumberOfVoices; i++)
    {
        pVoice = voices[i];
        if (pVoice->isActive() && pVoice->getFrequency() == fFrequency)
        {
            pVoice->noteOff(fTime);
        }
    }
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

    return value;
}

void VoiceManager::createVoices()
{
    for (int i = 0; i < NumberOfVoices; i++)
    {
        IEnvelope* env = new Envelope(); // created forever

        std::shared_ptr<IEnvelope> globalEnvelope = std::make_shared<Envelope>();
        std::shared_ptr<IOscillatorFunction> osc1 = std::make_shared<Sine>();
        std::shared_ptr<IOscillatorFunction> osc2 = std::make_shared<Square>();
        std::shared_ptr<IFilter> filter = std::make_shared<LowpassFilter>();

        IVoice* voice = new Voice(osc1, osc2, env, filter, m_pLfo, globalEnvelope);

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
    for (int i = 0; i < NumberOfVoices; i++)
    {
        IVoice* pVoice = voices[i];
        
        if(pVoice)
        {
            pVoice->getEnvelope()->setAttackTime(dAttackTime / 1000.0);
        }
    }
}

void VoiceManager::setEnvelopeReleaseTime(int dReleaseTime)
{
    for (int i = 0; i < NumberOfVoices; i++)
    {
        IVoice* pVoice = voices[i];
        
        if(pVoice)
        {
            pVoice->getEnvelope()->setReleaseTime(dReleaseTime / 1000.0);
        }
    }
}

void VoiceManager::setEnvelopeDecayTime(int dDecayTime)
{
    for (int i = 0; i < NumberOfVoices; i++)
    {
        IVoice* pVoice = voices[i];
        
        if(pVoice)
        {
            pVoice->getEnvelope()->setDecayTime(dDecayTime / 1000.0);
        }
    }
}

void VoiceManager::setEnvelopeSustainAmplitude(int dSustainAmplitude)
{
    for (int i = 0; i < NumberOfVoices; i++)
    {
        IVoice* pVoice = voices[i];
        
        if(pVoice)
        {
            pVoice->getEnvelope()->setSustainAmplitude(dSustainAmplitude / 1000.0);
        }
    }
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
    m_pLfo->setFrequency(frequency / 1000.0);
}

void VoiceManager::setLfoAmount(int amount)
{
    m_pLfo->setAmount(amount / 1000.0);
}

void VoiceManager::setLfoOscillator(std::shared_ptr<IOscillatorFunction> func)
{
    m_pLfo->setOscillator(func);
}

// GLOBAL ENVELOPE
void VoiceManager::setGlobalEnvelopeAttackTime(int dAttackTime)
{
    for (int i = 0; i < NumberOfVoices; i++)
    {
        IVoice* pVoice = voices[i];
        
        if(pVoice)
        {
            pVoice->getGlobalEnvelope()->setAttackTime(dAttackTime / 1000.0);
        }
    }
}

void VoiceManager::setGlobalEnvelopeReleaseTime(int dReleaseTime)
{
    for (int i = 0; i < NumberOfVoices; i++)
    {
        IVoice* pVoice = voices[i];
        
        if(pVoice)
        {
            pVoice->getGlobalEnvelope()->setReleaseTime(dReleaseTime / 1000.0);
        }
    }
}

void VoiceManager::setGlobalEnvelopeDecayTime(int dDecayTime)
{
    for (int i = 0; i < NumberOfVoices; i++)
    {
        IVoice* pVoice = voices[i];
        
        if(pVoice)
        {
            pVoice->getGlobalEnvelope()->setDecayTime(dDecayTime / 1000.0);
        }
    }
}

void VoiceManager::setGlobalEnvelopeSustainAmplitude(int dSustainAmplitude)
{
    for (int i = 0; i < NumberOfVoices; i++)
    {
        IVoice* pVoice = voices[i];
        
        if(pVoice)
        {
            pVoice->getGlobalEnvelope()->setSustainAmplitude(dSustainAmplitude / 1000.0);
        }
    }
}
