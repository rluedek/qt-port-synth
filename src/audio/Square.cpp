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

float Square::calculate(float& fTime, float fFrequency)
{
    return sin( 2. * M_PI * fFrequency * fTime) > 0 ? 1.0 : -1.0;
}