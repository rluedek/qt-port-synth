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

    virtual bool isNoteOff() = 0;
};

#endif