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
        , std::shared_ptr<modulation::IModulator> pModulator
        , std::shared_ptr<IEnvelope> pGlobalEnvelope);

    //dtor
    ~Voice();

    void noteOn(float fFrequency, float fTime) override;

    void noteOff(float fTime) override;

    float process(float fTime) override;

    void reset() override;

    bool isActive() override;
    void setActive() override;

    float getFrequency() override;

    std::shared_ptr<modulation::ModulationValue> getFilterCutOff();
    std::shared_ptr<modulation::ModulationValue> getFilterResonance();

private:
    std::shared_ptr<IOscillatorFunction> m_pOscillator1;
    std::shared_ptr<IOscillatorFunction> m_pOscillator2;
    IEnvelope* m_pEnvelope;
    std::shared_ptr<IFilter> m_pFilter;
    std::shared_ptr<IEnvelope> m_pGlobalEnvelope;
    float m_fFrequency;
    float m_fMix;
    bool m_bActive;

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

    std::shared_ptr<IEnvelope> getGlobalEnvelope() override;
    
    std::shared_ptr<IFilter> getFilter() override;
    void setFilter(FilterType type);

    void setOscillationMix(float fMix);
};

#endif