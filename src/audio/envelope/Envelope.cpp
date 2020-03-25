#include "Envelope.h"

Envelope::Envelope()
: m_dAttackTime(0.1)
, m_dDecayTime(0.01)
, m_dReleaseTime(2.0)
, m_dCurrentAmplitude(0.0)
, m_dActualSustainAmplitude(0.0)
, m_dSustainAmplitude(0.8)
, m_dStartAmplitude(1.0)
, m_bNoteOn(false)
, m_dTriggerOffTime(0.0)
, m_dTriggerOnTime(0.0)
{
}

Envelope::~Envelope()
{

}

void Envelope::noteOn(double dTime)
{
	m_dActualSustainAmplitude = 0.0;
	m_dTriggerOnTime = dTime;
	m_bNoteOn = true;
}

void Envelope::noteOff(double dTime)
{
	m_dTriggerOffTime = dTime;
	m_bNoteOn = false;
}

double Envelope::getAmplitude(double dTime)
{
	double dAmplitude = 0.0;

	if (m_bNoteOn)
	{
		double dLifeTime = dTime - m_dTriggerOnTime;

		if (dLifeTime <= m_dAttackTime)
		{
			// In attack Phase - approach max amplitude
			dAmplitude = (dLifeTime / m_dAttackTime) * m_dStartAmplitude;
		}

		else if (dLifeTime > m_dAttackTime && dLifeTime <= (m_dAttackTime + m_dDecayTime))
		{
			// In decay phase - reduce to sustained amplitude
			dAmplitude = ((dLifeTime - m_dAttackTime) / m_dDecayTime) * (m_dSustainAmplitude - m_dStartAmplitude) + m_dStartAmplitude;
		}

		else if (dLifeTime > (m_dAttackTime + m_dDecayTime))
		{
			// In sustain phase - dont change until note released
			dAmplitude = m_dSustainAmplitude;
		}
		m_dActualSustainAmplitude = dAmplitude;
	}
	else
	{
		double dLifeTime = dTime - m_dTriggerOffTime;

		// Note has been released, so in release phase
		dAmplitude = ((dLifeTime) / m_dReleaseTime) * (0.0 - m_dActualSustainAmplitude) + m_dActualSustainAmplitude;
	}

	// Amplitude should not be negative
	if (dAmplitude <= 0.0001)
		dAmplitude = 0.0;

	m_dCurrentAmplitude = dAmplitude;

	return dAmplitude;
}

double Envelope::getCurrentAmplitude()
{
	return m_dCurrentAmplitude;
}

bool Envelope::setAttackTime(double dAttackTime)
{
	if (dAttackTime <= 0.0)
	{
		dAttackTime = 0.01;
	}

	m_dAttackTime = dAttackTime;
	return true;
}

double Envelope::getAttackTime()
{
	return m_dAttackTime;
}


bool Envelope::setDecayTime(double dDecayTime)
{
	m_dDecayTime = dDecayTime;
	return true;
}

bool Envelope::setReleaseTime(double dReleaseTime)
{

	m_dReleaseTime = dReleaseTime;
	return true;
}

double Envelope::getReleaseTime()
{
	return m_dReleaseTime;
}

bool Envelope::setSustainAmplitude(double dSustainAmplitude)
{
	m_dSustainAmplitude = dSustainAmplitude;
	return true;
}