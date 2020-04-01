#include "IOscillatorFunction.h"

#include <cmath>

//ctor
Sine::Sine()
{
    
}

 //dtor
 Sine::~Sine()
 {

 }

float Sine::calculate(float& fTime, float fFrequency)
{
    return sin( 2. * M_PI * fFrequency * fTime);
}