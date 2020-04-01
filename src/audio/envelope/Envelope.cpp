#include "Envelope.h"

Envelope::Envelope()
: m_fAttackTime(0.1)
, m_fDecayTime(0.01)
, m_fReleaseTime(2.0)
, m_fCurrentAmplitude(0.0)
, m_fActualSustainAmplitude(0.0)
, m_fSustainAmplitude(0.8)
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

		if (fLifeTime <= m_fAttackTime)
		{
			// In attack Phase - approach max amplitude
			fAmplitude = (fLifeTime / m_fAttackTime) * m_fStartAmplitude;
		}

		else if (fLifeTime > m_fAttackTime && fLifeTime <= (m_fAttackTime + m_fDecayTime))
		{
			// In decay phase - reduce to sustained amplitude
			fAmplitude = ((fLifeTime - m_fAttackTime) / m_fDecayTime) * (m_fSustainAmplitude - m_fStartAmplitude) + m_fStartAmplitude;
		}

		else if (fLifeTime > (m_fAttackTime + m_fDecayTime))
		{
			// In sustain phase - dont change until note released
			fAmplitude = m_fSustainAmplitude;
		}
		m_fActualSustainAmplitude = fAmplitude;
	}
	else
	{
		fLifeTime = fTime - m_fTriggerOffTime;

		// Note has been released, so in release phase
		fAmplitude = ((fLifeTime) / m_fReleaseTime) * (0.0 - m_fActualSustainAmplitude) + m_fActualSustainAmplitude;
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

bool Envelope::setAttackTime(float fAttackTime)
{
	if (fAttackTime <= 0.0)
	{
		fAttackTime = 0.01;
	}

	m_fAttackTime = fAttackTime;
	return true;
}

float Envelope::getAttackTime()
{
	return m_fAttackTime;
}


bool Envelope::setDecayTime(float fDecayTime)
{
	m_fDecayTime = fDecayTime;
	return true;
}

bool Envelope::setReleaseTime(float fReleaseTime)
{

	m_fReleaseTime = fReleaseTime;
	return true;
}

float Envelope::getReleaseTime()
{
	return m_fReleaseTime;
}

bool Envelope::setSustainAmplitude(float fSustainAmplitude)
{
	m_fSustainAmplitude = fSustainAmplitude;
	return true;
}

bool Envelope::isNoteOff()
{
	return (!m_bNoteOn);
}
