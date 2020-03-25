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

double Sine::calculate(double& time, double frequency)
{
    return sin( 2. * M_PI * frequency * time);
}