#ifndef MODULATION_VALUE_H
#define MODULATION_VALUE_H

#include <memory>

#include "IModulator.h"

namespace modulation
{
    class ModulationValue
    {
    public:
        ModulationValue(double dMinValue, double dMaxValue);

        double getModulatedValue();

        double getValue();
        void setValue(double);

        void setModulator(std::shared_ptr<IModulator> pModulator);
    

    private:
        double m_dValue;
        double m_dModulatedValue;
        double m_dMinValue;
        double m_dMaxValue;
        
        std::shared_ptr<modulation::IModulator> m_pModulator;
    };
}

#endif