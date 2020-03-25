#ifndef IENVELOPE_H
#define IENVELOPE_H

class IEnvelope
{
public:
    virtual void noteOn(double dTime) = 0;
    virtual void noteOff(double dTime) = 0;
    virtual double getAmplitude(double dTime) = 0;
    virtual double getCurrentAmplitude() = 0;

    /*
    * Parameters
    */
    virtual bool setAttackTime(double dAttackTime) = 0;
    virtual double getAttackTime() = 0;

    virtual bool setDecayTime(double dDecayTime) = 0;

    virtual bool setReleaseTime(double dReleaseTime) = 0;
    virtual double getReleaseTime() = 0;

    virtual bool setSustainAmplitude(double dSustainAmplitude) = 0;
};

#endif