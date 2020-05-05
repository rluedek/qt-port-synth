/**
 * @copyright Copyright (c) 2020 Rico Luedeke
 * @author Rico Luedeke
 * @brief  This file is part of qt-port-synth (A baisc synthesizer using PortAudio and Qt5)
 * @date 2020-05-04
 * @see https://github.com/rluedek/qt-port-synth
 */

#ifndef VOICEMANAGER_H
#define VOICEMANAGER_H

#include "audio/voice/IVoice.h"
#include <QObject>

#include "audio/oscillator/Lfo.h"
#include "audio/IOscillatorFunction.h"
#include "audio/filter/FilterTypes.h"

class VoiceManager : public QObject
{
public:
    //ctor
    VoiceManager();

    static const int NumberOfVoices = 20;

    void noteOn(float fFrequency, float fTime);

    void noteOff(float fFrequency, float fTime);

    float getSample(float fTime);

    //Gain
    void setGain(int gain);

    //Oscillators
    void setOscillator1(std::shared_ptr<IOscillatorFunction> func);
    void setOscillator2(std::shared_ptr<IOscillatorFunction> func);
    void setOscillatorMix(int mix);
        
    // Envelope
    void setEnvelopeAttackTime(int dAttackTime);
    void setEnvelopeReleaseTime(int dReleaseTime);
    void setEnvelopeDecayTime(int dDecayTime);
    void setEnvelopeSustainAmplitude(int dSustainAmplitude);

    //Global envelope
    void setGlobalEnvelopeAttackTime(int dAttackTime);
    void setGlobalEnvelopeReleaseTime(int dReleaseTime);
    void setGlobalEnvelopeDecayTime(int dDecayTime);
    void setGlobalEnvelopeSustainAmplitude(int dSustainAmplitude);

    // Filter
    void setFilter(FilterType type);
    void setCutOffFrequency(int frequency);
    void setResonance(int resonance);

    //Lfo
    void setLfo(std::shared_ptr<Lfo> pLfo);
    void setLfoFrequency(int frequency);
    void setLfoAmount(int amount);
    void setLfoOscillator(std::shared_ptr<IOscillatorFunction> func);

private:

    IVoice* voices[NumberOfVoices];

    IVoice* findFreeVoice();

    std::shared_ptr<Lfo>        m_pLfo;

/******************************************************************************
Parameters
******************************************************************************/
    std::shared_ptr<Param> m_pGain;
    std::shared_ptr<Param> m_pOscillatorMix;
    std::shared_ptr<Param> m_pEnvelopeAttackTime;
    std::shared_ptr<Param> m_pEnvelopeReleaseTime;
    std::shared_ptr<Param> m_pEnvelopeDecayTime;
    std::shared_ptr<Param> m_pEnvelopeSustainAmplitude;
    std::shared_ptr<Param> m_pFilterEnvelopeAttackTime;
    std::shared_ptr<Param> m_pFilterEnvelopeReleaseTime;
    std::shared_ptr<Param> m_pFilterEnvelopeDecayTime;
    std::shared_ptr<Param> m_pFilterEnvelopeSustainAmplitude;
    std::shared_ptr<Param> m_pLfoFrequency;
    std::shared_ptr<Param> m_pLfoAmount;

    void createVoices();    
};

#endif