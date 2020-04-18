#ifndef MODULATION_VALUE_H
#define MODULATION_VALUE_H

#include <memory>

#include "IModulator.h"
#include "audio/envelope/IEnvelope.h"
#include "audio/voicemanager/Param.h"

namespace modulation
{
    class ModulationValue : public Param
    {
    public:
        ModulationValue(float fMinValue, float fMaxValue, float fDefaultValue);

        float getModulatedValue(float fTime);

        void setModulator(std::shared_ptr<IModulator> pModulator);
        void setEnvelopeModulator(std::shared_ptr<IEnvelope> pEnvelopeModulator);

    private:
        bool    m_bActivated;
        
        std::shared_ptr<modulation::IModulator> m_pModulator;
        std::shared_ptr<IEnvelope> m_pEnvelopeGenerator;
    };
}

#endif