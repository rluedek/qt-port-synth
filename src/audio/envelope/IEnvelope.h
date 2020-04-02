#ifndef IENVELOPE_H
#define IENVELOPE_H

class IEnvelope
{
public:
    virtual void noteOn(float fTime) = 0;
    virtual void noteOff(float fTime) = 0;
    virtual float getAmplitude(float fTime) = 0;
    virtual float getCurrentAmplitude() = 0;
    virtual void reset() = 0;

    /*
    * Parameters
    */
    virtual bool setAttackTime(float fAttackTime) = 0;
    virtual float getAttackTime() = 0;

    virtual bool setDecayTime(float fDecayTime) = 0;

    virtual bool setReleaseTime(float fReleaseTime) = 0;
    virtual float getReleaseTime() = 0;

    virtual bool setSustainAmplitude(float fSustainAmplitude) = 0;

    virtual bool isNoteOff() = 0;
};

#endif