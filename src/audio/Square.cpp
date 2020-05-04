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
Square::Square()
{
    
}

 //dtor
 Square::~Square()
 {
     
 }

float Square::calculate(float fTime, float fFrequency)
{
    return sin( 2. * M_PI * fFrequency * fTime) > 0 ? 1.0 : -1.0;
}