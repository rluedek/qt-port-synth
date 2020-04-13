#ifndef IMODULATIOR_H
#define IMODULATIOR_H

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