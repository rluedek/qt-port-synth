#include "IOscillatorFunction.h"

#include <cmath>

Triangle::Triangle()
{

}

Triangle::~Triangle()
{

}

float Triangle::calculate(float fTime, float fFrequency)
{
    return asin(sin(2.0 * M_PI * fFrequency * fTime)) * (2.0 / M_PI);
}