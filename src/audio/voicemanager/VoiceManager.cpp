#include "audio/voicemanager/VoiceManager.h"

#include <iostream>
#include <memory>

#include "qdebug.h"

#include "audio/envelope/Envelope.h"
#include "audio/filter/LowpassFilter.h"
#include "audio/voice/Voice.h"


VoiceManager::VoiceManager()
{
    Lfo lfo;
    std::shared_ptr<IOscillatorFunction> lfoOsc = std::make_shared<Sine>();
    lfo.setOscillator(lfoOsc);
    m_pLfo = std::make_shared<Lfo>(lfo);
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

void VoiceManager::noteOn(double dFrequency, double dTime)
{
    IVoice* pVoice = findFreeVoice();

    if (pVoice)
    {   
        pVoice->noteOn(dFrequency, dTime);
    }
}

void VoiceManager::noteOff(double dFrequency, double dTime)
{
    IVoice* pVoice = nullptr;
    for (int i = 0; i < NumberOfVoices; i++)
    {
        pVoice = voices[i];
        if (pVoice->isActive() && pVoice->getFrequency() == dFrequency)
        {
            pVoice->noteOff(dTime);
        }
    }
}

float VoiceManager::getSample(double time)
{   
    float value = 0.0;
    IVoice* pVoice = nullptr;
    m_pLfo->trigger(time);
    for (int i = 0; i < NumberOfVoices; i++)
    {
        pVoice = voices[i];
        if (true) // TODO: check if its active
        {
            value += pVoice->process(time);
        }
    }

    return value;
}

void VoiceManager::createVoices()
{
    for (int i = 0; i < NumberOfVoices; i++)
    {
        IEnvelope* env = new Envelope(); // created forever
        
        std::shared_ptr<IOscillatorFunction> osc1 = std::make_shared<Sine>();
        std::shared_ptr<IOscillatorFunction> osc2 = std::make_shared<Square>(); 
        std::shared_ptr<IFilter> filter = std::make_shared<LowpassFilter>();

        IVoice* voice = new Voice(osc1, osc2, env, filter, m_pLfo);

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

void VoiceManager::setFilter(std::shared_ptr<IFilter> pFilter)
{
    for (int i = 0; i < NumberOfVoices; i++)
    {
        IVoice* pVoice = voices[i];
        
        if(pVoice)
        {
            pVoice->setFilter(pFilter);
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
            //pVoice->getFilter()->setCutoffFrequency(frequency / 1000.0);
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
            //pVoice->getFilter()->setResonance(resonance / 1000.0);
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
    