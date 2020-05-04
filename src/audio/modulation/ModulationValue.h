#ifndef MODULATION_VALUE_H
#define MODULATION_VALUE_H

#include <memory>

#include "audio/oscillator/ILfo.h"
#include "audio/envelope/IEnvelope.h"
#include "audio/voicemanager/Param.h"

namespace modulation
{
    class ModulationValue : public Param
    {
    public:
        ModulationValue(float fMinValue, float fMaxValue, float fDefaultValue);

        float getModulatedValue(float fTime);

        void setLfo(std::shared_ptr<ILfo> pModulator);
        void setEnvelopeModulator(std::shared_ptr<IEnvelope> pEnvelopeModulator);

    private:
        bool    m_bActivated;
        
        std::shared_ptr<ILfo> m_pLfo;
        std::shared_ptr<IEnvelope> m_pEnvelopeGenerator;
    };
}

#endif