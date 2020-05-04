/**
 * @copyright Copyright (c) 2020 Rico Luedeke
 * @author Rico Luedeke
 * @brief  This file is part of qt-port-synth (A baisc synthesizer using PortAudio and Qt5)
 * @date 2020-05-04
 * @see https://github.com/rluedek/qt-port-synth
 */

#ifndef ENVELOPE_H
#define ENVELOPE_H

#include <memory>

#include "audio/envelope/IEnvelope.h"
#include "audio/voicemanager/Param.h"

class Envelope : public IEnvelope
{
public:

    //ctor
    Envelope( std::shared_ptr<Param> pAttackTime
            , std::shared_ptr<Param> pDecayTime
            , std::shared_ptr<Param> pReleaseTime
            , std::shared_ptr<Param> pSustainAmplitude);

    //dtor
    virtual ~Envelope();

    void noteOn(float fTime) override;
    void noteOff(float fTime) override;
    float getAmplitude(float fTime) override;
    float getCurrentAmplitude() override;
    void reset() override;
    bool isNoteOff() override;


private:
    std::shared_ptr<Param> m_pAttackTime;
    std::shared_ptr<Param> m_pDecayTime;
    std::shared_ptr<Param> m_pReleaseTime;
    std::shared_ptr<Param> m_pSustainAmplitude;
    
    float m_fActualSustainAmplitude;
    float m_fStartAmplitude;
    float m_fTimeNoteOn;
    float m_fTimeNoteOff;
	float m_fTriggerOffTime;
	float m_fTriggerOnTime;
    float m_fCurrentAmplitude;
    
    bool m_bNoteOn;
};

#endif