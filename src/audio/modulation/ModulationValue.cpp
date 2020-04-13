#include "ModulationValue.h"

#include <math.h>

namespace modulation
{
    ModulationValue::ModulationValue(float fMinValue, float fMaxValue)
    : m_fValue(0.0)
    , m_fMinValue(fMinValue)
    , m_fMaxValue(fMaxValue)
    {

    }

    float ModulationValue::getModulatedValue(float fTime)
    {
        float amplitude = 1;
        if (m_pEnvelopeGenerator)
        {
            amplitude = m_pEnvelopeGenerator->getAmplitude(fTime);
        }

        return fmax(fmin( amplitude * (m_fValue + m_pModulator->getModulationAmount()), m_fMaxValue), m_fMinValue);
    }

    float ModulationValue::getValue()
    {
        return m_fValue;
    }

    void ModulationValue::setValue(float fValue)
    {
        m_fValue = fValue;
    }

    void ModulationValue::setModulator(std::shared_ptr<IModulator> pModulator)
    {
        m_pModulator = pModulator;
    }

    void ModulationValue::setEnvelopeModulator(std::shared_ptr<IEnvelope> pEnvelopeModulator)
    {
        m_pEnvelopeGenerator = pEnvelopeModulator;
    }
}