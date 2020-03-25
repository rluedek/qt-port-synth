#ifndef IMODULATIOR_H
#define IMODULATIOR_H

#include <memory>

namespace modulation
{
    class IModulator
    {
    public:

        virtual void trigger(double dTime) = 0;
        virtual double getModulationAmount() = 0;
    };
}

#endif