#ifndef ENVELOPE_H
#define ENVELOPE_H

#include "audio/envelope/IEnvelope.h"

class Envelope : public IEnvelope
{
public:

    //ctor
    Envelope();
    //dtor
    virtual ~Envelope();

    void noteOn(float fTime) override;
    void noteOff(float fTime) override;
    float getAmplitude(float fTime) override;
    float getCurrentAmplitude() override;

    bool setAttackTime(float fAttackTime) override;
    float getAttackTime() override;

    bool setDecayTime(float fDecayTime) override;

    bool setReleaseTime(float fReleaseTime) override;
    float getReleaseTime() override;

    bool setSustainAmplitude(float fSustainAmplitude) override;

    bool isNoteOff() override;


private:
    float m_fAttackTime;
    float m_fDecayTime;
    float m_fReleaseTime;
    float m_fActualSustainAmplitude;
    float m_fSustainAmplitude;
    float m_fStartAmplitude;
    float m_fTimeNoteOn;
    float m_fTimeNoteOff;
	float m_fTriggerOffTime;
	float m_fTriggerOnTime;
    float m_fCurrentAmplitude;
    
    bool m_bNoteOn;
};

#endif