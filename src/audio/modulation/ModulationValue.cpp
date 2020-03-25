#include "ModulationValue.h"

#include <math.h>

namespace modulation
{
    ModulationValue::ModulationValue(double dMinValue, double dMaxValue)
    : m_dValue(0.0)
    , m_dModulatedValue(0.0)
    , m_dMinValue(dMinValue)
    , m_dMaxValue(dMaxValue)
    {

    }

    double ModulationValue::getModulatedValue()
    {
        return fmax(fmin(m_dValue + m_pModulator->getModulationAmount(), m_dMaxValue), m_dMinValue);
    }

    double ModulationValue::getValue()
    {
        return m_dValue;
    }

    void ModulationValue::setValue(double dValue)
    {
        m_dValue = dValue;
    }

    void ModulationValue::setModulator(std::shared_ptr<IModulator> pModulator)
    {
        m_pModulator = pModulator;
    }
}