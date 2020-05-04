/**
 * @copyright Copyright (c) 2020 Rico Luedeke
 * @author Rico Luedeke
 * @brief  This file is part of qt-port-synth (A baisc synthesizer using PortAudio and Qt5)
 * @date 2020-05-04
 * @see https://github.com/rluedek/qt-port-synth
 */

#ifndef VOICE_H
#define VOICE_H

#include "IVoice.h"
#include "audio/voicemanager/Param.h"
#include "audio/oscillator/Lfo.h"

class Voice : public IVoice
{
public:
    // ctor
    Voice(std::shared_ptr<IOscillatorFunction> pOscillator1
        , std::shared_ptr<IOscillatorFunction> pOscillator2
        , std::shared_ptr<IFilter> pFilter
        , std::shared_ptr<ILfo> pLfo
        , std::shared_ptr<IEnvelope> pFilterEnvelope
        , std::shared_ptr<IEnvelope> pAmpEnvelope);
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
    std::shared_ptr<IFilter> m_pFilter;
    std::shared_ptr<IEnvelope> m_pAmpEnvelope;
    std::shared_ptr<IEnvelope> m_pFilterEnvelope;
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

    std::shared_ptr<IEnvelope> getAmpEnvelope() override;
    
    std::shared_ptr<IEnvelope> getFilterEnvelope() override;
    
    std::shared_ptr<IFilter> getFilter() override;
    void setFilter(FilterType type);

    void setOscillationMix(float fMix);
};

#endif