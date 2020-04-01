#ifndef VOICEMANAGER_H
#define VOICEMANAGER_H

#include "audio/voice/IVoice.h"
#include <QObject>

#include "audio/oscillator/Lfo.h"
#include "audio/IOscillatorFunction.h"

class VoiceManager : public QObject
{
public:
    //ctor
    VoiceManager();

    static const int NumberOfVoices = 20;

    void noteOn(float fFrequency, float fTime);

    void noteOff(float fFrequency, float fTime);

    float getSample(float fTime);

    //Oscillators
    void setOscillator1(std::shared_ptr<IOscillatorFunction> func);
    void setOscillator2(std::shared_ptr<IOscillatorFunction> func);
        
    // Envelope
    void setEnvelopeAttackTime(int dAttackTime);
    void setEnvelopeReleaseTime(int dReleaseTime);
    void setEnvelopeDecayTime(int dDecayTime);
    void setEnvelopeSustainAmplitude(int dSustainAmplitude);

    // Filter
    void setFilter(std::shared_ptr<IFilter> pFilter);
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

    std::shared_ptr<Lfo>    m_pLfo;

    void createVoices();
};

#endif