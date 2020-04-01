#ifndef IMODULATIOR_H
#define IMODULATIOR_H

#include <memory>

namespace modulation
{
    class IModulator
    {
    public:

        virtual void trigger(float fTime) = 0;
        virtual float getModulationAmount() = 0;
    };
}

#endif