/**
 * @copyright Copyright (c) 2020 Rico Luedeke
 * @author Rico Luedeke
 * @brief  This file is part of qt-port-synth (A baisc synthesizer using PortAudio and Qt5)
 * @date 2020-05-04
 * @see https://github.com/rluedek/qt-port-synth
 */

#include "IOscillatorFunction.h"

#include <cmath>

//ctor
Saw::Saw()
{
    
}

 //dtor
 Saw::~Saw()
 {

 }

float Saw::calculate(float fTime, float fFrequency)
{
    float x = fTime * fFrequency;

    return x - floorf32(x);
}