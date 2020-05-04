#ifndef LFO_H
#define LFO_H

#include "audio/oscillator/ILfo.h"
#include "audio/voicemanager/Param.h"

#include <memory>

class Lfo : public ILfo
{
public:
    Lfo(std::shared_ptr<Param> pFrequency
        , std::shared_ptr<Param> pAmount);

    void setOscillator(std::shared_ptr<IOscillatorFunction> pOscillator) override;

    void trigger(float fTime) override;
    float getModulationAmount() override;

private:
    std::shared_ptr<Param> m_pFrequency;
    std::shared_ptr<Param> m_pAmount;

    float m_fModulationAmount;
    std::shared_ptr<IOscillatorFunction> m_pOscillator;
};
#endif