#ifndef MODULATION_VALUE_H
#define MODULATION_VALUE_H

#include <memory>

#include "IModulator.h"

namespace modulation
{
    class ModulationValue
    {
    public:
        ModulationValue(float fMinValue, float fMaxValue);

        float getModulatedValue();

        float getValue();
        void setValue(float);

        void setModulator(std::shared_ptr<IModulator> pModulator);
    

    private:
        float m_fValue;
        float m_fModulatedValue;
        float m_fMinValue;
        float m_fMaxValue;
        
        std::shared_ptr<modulation::IModulator> m_pModulator;
    };
}

#endif