#ifndef LFO_H
#define LFO_H

#include "audio/oscillator/ILfo.h"
#include "audio/modulation/IModulator.h"

class Lfo : public ILfo, public modulation::IModulator
{
public:
    Lfo();

    void setFrequency(double dFrequency) override;
    void setAmount(double dAmount) override;
    void setOscillator(std::shared_ptr<IOscillatorFunction> pOscillator) override;

    void trigger(double dTime) override;
    double getModulationAmount() override;

private:
    double m_dFrequency;
    double m_dAmount;
    double m_dModulationAmount;
    std::shared_ptr<IOscillatorFunction> m_pOscillator;
};
#endif