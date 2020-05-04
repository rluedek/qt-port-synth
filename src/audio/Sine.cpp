/**
 * @copyright Copyright (c) 2020 Rico Luedeke
 * @author Rico Luedeke
 * @brief  This file is part of qt-port-synth (A baisc synthesizer using PortAudio and Qt5)
 * @date 2020-05-04
 * @see https://github.com/rluedek/qt-port-synth
 */

#include "IOscillatorFunction.h"

#include <cmath>

#include <iostream>

//ctor
Sine::Sine()
{
    
}

 //dtor
 Sine::~Sine()
 {

 }

float Sine::calculate(float fTime, float fFrequency)
{
    return sin( 2. * M_PI * fFrequency * fTime);
}