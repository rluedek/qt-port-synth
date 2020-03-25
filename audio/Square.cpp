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

double Square::calculate(double& time, double frequency)
{
    return sin( 2. * M_PI * frequency * time) > 0 ? 1.0 : -1.0;
}