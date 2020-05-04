/**
 * @copyright Copyright (c) 2020 Rico Luedeke
 * @author Rico Luedeke
 * @brief  This file is part of qt-port-synth (A baisc synthesizer using PortAudio and Qt5)
 * @date 2020-05-04
 * @see https://github.com/rluedek/qt-port-synth
 */

#include "Param.h"
#include "qdebug.h"

Param::Param(float fMinValue, float fMaxValue, float fDefaultValue)
: m_fMaxValue(fMaxValue)
, m_fMinValue(fMinValue)
, m_fValue(fDefaultValue)
{

}

float Param::getValue()
{
    return m_fValue;
}

void Param::setValue(float fValue)
{
    if (fValue <= m_fMaxValue && fValue >= m_fMinValue)
    {
        qDebug() << "Setting value to " << fValue;
        m_fValue = fValue;
    }
}

void Param::setMinValue(float fMinValue)
{
    m_fMinValue = fMinValue;
}

float Param::getMinValue()
{
    return m_fMinValue;
}

void Param::setMaxValue(float fMaxValue)
{
    m_fMaxValue = fMaxValue;
}

float Param::getMaxValue()
{
    return m_fMaxValue;
}