/**
 * @copyright Copyright (c) 2020 Rico Luedeke
 * @author Rico Luedeke
 * @brief  This file is part of qt-port-synth (A baisc synthesizer using PortAudio and Qt5)
 * @date 2020-05-04
 * @see https://github.com/rluedek/qt-port-synth
 */

#ifndef IPARAM_H
#define IPARAM_H

class Param
{
public:

    Param(float fMinValue, float fMaxValue, float fDefaultValue);

    float getValue();
    void setValue(float);

    float getMinValue();
    void setMinValue(float fMinValue);
    
    float getMaxValue();
    void setMaxValue(float fMaxValue);

protected:

    float   m_fValue;
    float   m_fMinValue;
    float   m_fMaxValue;
};

#endif