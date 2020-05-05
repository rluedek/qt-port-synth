/**
 * @copyright Copyright (c) 2020 Rico Luedeke
 * @author Rico Luedeke
 * @brief  This file is part of qt-port-synth (A baisc synthesizer using PortAudio and Qt5)
 * @date 2020-05-04
 * @see https://github.com/rluedek/qt-port-synth
 */

#include "ModulationValue.h"

#include <math.h>

namespace modulation
{
    ModulationValue::ModulationValue(float fMinValue, float fMaxValue, float fDefaultValue)
    : Param(fMinValue, fMaxValue, fDefaultValue)
    , m_bActivated(true)
    {

    }

    float ModulationValue::getModulatedValue(float fTime)
    {
        if(m_bActivated)
        {
            float amplitude = 1;
            if (m_pEnvelopeGenerator)
            {
                amplitude = m_pEnvelopeGenerator->getAmplitude(fTime);
            }

            return fmax(fmin( amplitude * (m_fValue + m_pLfo->getModulationAmount()), m_fMaxValue), m_fMinValue);
        }

        return getValue();
    }

    void ModulationValue::setLfo(std::shared_ptr<ILfo> pModulator)
    {
        m_pLfo = pModulator;
    }

    void ModulationValue::setEnvelopeModulator(std::shared_ptr<IEnvelope> pEnvelopeModulator)
    {
        m_pEnvelopeGenerator = pEnvelopeModulator;
    }
}