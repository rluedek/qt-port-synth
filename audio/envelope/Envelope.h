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

    void noteOn(double dTime) override;
    void noteOff(double dTime) override;
    double getAmplitude(double dTime) override;
    double getCurrentAmplitude() override;

    bool setAttackTime(double dAttackTime) override;
    double getAttackTime() override;

    bool setDecayTime(double dDecayTime) override;

    bool setReleaseTime(double dReleaseTime) override;
    double getReleaseTime() override;

    bool setSustainAmplitude(double dSustainAmplitude) override;
private:

    double m_dAttackTime;
    double m_dDecayTime;
    double m_dReleaseTime;
    double m_dActualSustainAmplitude;
    double m_dSustainAmplitude;
    double m_dStartAmplitude;
    double m_dTimeNoteOn;
    double m_dTimeNoteOff;
	double m_dTriggerOffTime;
	double m_dTriggerOnTime;
    double m_dCurrentAmplitude;
    
    bool m_bNoteOn;

};

#endif