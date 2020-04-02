#include "ModulationValue.h"

#include <math.h>

namespace modulation
{
    ModulationValue::ModulationValue(float fMinValue, float fMaxValue)
    : m_fValue(0.0)
    , m_fModulatedValue(0.0)
    , m_fMinValue(fMinValue)
    , m_fMaxValue(fMaxValue)
    {

    }

    float ModulationValue::getModulatedValue()
    {
        return fmax(fmin(m_fValue + m_pModulator->getModulationAmount(), m_fMaxValue), m_fMinValue);
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
}