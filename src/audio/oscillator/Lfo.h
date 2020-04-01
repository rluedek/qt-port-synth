#ifndef LFO_H
#define LFO_H

#include "audio/oscillator/ILfo.h"
#include "audio/modulation/IModulator.h"

class Lfo : public ILfo, public modulation::IModulator
{
public:
    Lfo();

    void setFrequency(float fFrequency) override;
    void setAmount(float fAmount) override;
    void setOscillator(std::shared_ptr<IOscillatorFunction> pOscillator) override;

    void trigger(float fTime) override;
    float getModulationAmount() override;

private:
    float m_fFrequency;
    float m_fAmount;
    float m_fModulationAmount;
    std::shared_ptr<IOscillatorFunction> m_pOscillator;
};
#endif