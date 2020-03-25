#ifndef VOICE_H
#define VOICE_H

#include "IVoice.h"
#include "audio/modulation/IModulator.h"

class Voice : public IVoice
{
public:
    // ctor
    Voice(std::shared_ptr<IOscillatorFunction> pOscillator1
        , std::shared_ptr<IOscillatorFunction> pOscillator2
        , IEnvelope* pEnvelope
        , std::shared_ptr<IFilter> pFilter
        , std::shared_ptr<modulation::IModulator> pModulator);

    //dtor
    ~Voice();

    void noteOn(double dFrequency, double dTime) override;

    void noteOff(double dTime) override;

    double process(double dTime) override;

    bool isActive() override;

    double getFrequency() override;

    std::shared_ptr<modulation::ModulationValue> getFilterCutOff();
    std::shared_ptr<modulation::ModulationValue> getFilterResonance();

private:
    std::shared_ptr<IOscillatorFunction> m_pOscillator1;
    std::shared_ptr<IOscillatorFunction> m_pOscillator2;
    IEnvelope* m_pEnvelope;
    std::shared_ptr<IFilter> m_pFilter;
    double m_dFrequency;

/******************************************************************************
    Modulation
******************************************************************************/
    std::shared_ptr<modulation::ModulationValue> m_pFilterCutOff;
    std::shared_ptr<modulation::ModulationValue> m_pFilterResonance;

/******************************************************************************
    Setters and Getters
******************************************************************************/

    std::shared_ptr<IOscillatorFunction> getOscillator1() override;
    void setOscillator1(std::shared_ptr<IOscillatorFunction> rOscillator) override;
     
    std::shared_ptr<IOscillatorFunction> getOscillator2() override;
    void setOscillator2(std::shared_ptr<IOscillatorFunction> rOscillator) override;

    IEnvelope* getEnvelope() override;
    void setEnvelope(IEnvelope* pEnvelope) override;
    
    std::shared_ptr<IFilter> getFilter() override;
    void setFilter(std::shared_ptr<IFilter> pFilter) override;
};

#endif