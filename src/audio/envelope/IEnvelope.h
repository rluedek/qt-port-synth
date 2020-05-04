/**
 * @copyright Copyright (c) 2020 Rico Luedeke
 * @author Rico Luedeke
 * @brief  This file is part of qt-port-synth (A baisc synthesizer using PortAudio and Qt5)
 * @date 2020-05-04
 * @see https://github.com/rluedek/qt-port-synth
 */

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