/**
 * @copyright Copyright (c) 2020 Rico Luedeke
 * @author Rico Luedeke
 * @brief  This file is part of qt-port-synth (A baisc synthesizer using PortAudio and Qt5)
 * @date 2020-05-04
 * @see https://github.com/rluedek/qt-port-synth
 */

#include "Envelope.h"

Envelope::Envelope( std::shared_ptr<Param> pAttackTime
    	, std::shared_ptr<Param> pDecayTime
    	, std::shared_ptr<Param> pReleaseTime
    	, std::shared_ptr<Param> pSustainAmplitude)
: m_pAttackTime(pAttackTime)
, m_pDecayTime(pDecayTime)
, m_pReleaseTime(pReleaseTime)
, m_pSustainAmplitude(pSustainAmplitude)
, m_fCurrentAmplitude(0.0)
, m_fActualSustainAmplitude(0.0)
, m_fStartAmplitude(1.0)
, m_bNoteOn(false)
, m_fTriggerOffTime(0.0)
, m_fTriggerOnTime(0.0)
{
}

Envelope::~Envelope()
{

}

void Envelope::noteOn(float fTime)
{
	m_fActualSustainAmplitude = 0.0;
	m_fTriggerOnTime = fTime;
	m_bNoteOn = true;
}

void Envelope::noteOff(float fTime)
{
	m_fTriggerOffTime = fTime;
	m_bNoteOn = false;
}

float Envelope::getAmplitude(float fTime)
{
	float fAmplitude = 0.0;
	float fLifeTime = 0.0;

	if (m_bNoteOn)
	{
		fLifeTime = fTime - m_fTriggerOnTime;

		if (fLifeTime <= m_pAttackTime->getValue())
		{
			// In attack Phase - approach max amplitude
			fAmplitude = (fLifeTime / m_pAttackTime->getValue()) * m_fStartAmplitude;
		}

		else if (fLifeTime > m_pAttackTime->getValue() && fLifeTime <= (m_pAttackTime->getValue() + m_pDecayTime->getValue()))
		{
			// In decay phase - reduce to sustained amplitude
			fAmplitude = ((fLifeTime - m_pAttackTime->getValue()) / m_pDecayTime->getValue()) * (m_pSustainAmplitude->getValue() - m_fStartAmplitude) + m_fStartAmplitude;
		}

		else if (fLifeTime > (m_pAttackTime->getValue() + m_pDecayTime->getValue()))
		{
			// In sustain phase - dont change until note released
			fAmplitude = m_pSustainAmplitude->getValue();
		}
		m_fActualSustainAmplitude = fAmplitude;
	}
	else
	{
		fLifeTime = fTime - m_fTriggerOffTime;

		// Note has been released, so in release phase
		fAmplitude = ((fLifeTime) / m_pReleaseTime->getValue()) * (0.0 - m_fActualSustainAmplitude) + m_fActualSustainAmplitude;
	}

	// Amplitude should not be negative
	if (fAmplitude <= 0.0001)
		fAmplitude = 0.0;

	m_fCurrentAmplitude = fAmplitude;

	return fAmplitude;
}

float Envelope::getCurrentAmplitude()
{
	return m_fCurrentAmplitude;
}

void Envelope::reset()
{
	m_bNoteOn = false;
	m_fCurrentAmplitude = 0.0;
	m_fTriggerOffTime = 0.0;
	m_fTriggerOnTime = 0.0;
}

bool Envelope::isNoteOff()
{
	return (!m_bNoteOn);
}
