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