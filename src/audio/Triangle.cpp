#include "IOscillatorFunction.h"

#include <cmath>

Triangle::Triangle()
{

}

Triangle::~Triangle()
{

}

double Triangle::calculate(double& time, double frequency)
{
    return asin(sin(2.0 * M_PI * frequency * time)) * (2.0 / M_PI);
}