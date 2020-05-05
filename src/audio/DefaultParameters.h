/**
 * @copyright Copyright (c) 2020 Rico Luedeke
 * @author Rico Luedeke
 * @brief  This file is part of qt-port-synth (A basic synthesizer using PortAudio and Qt5)
 * @date 2020-05-05
 * @see https://github.com/rluedek/qt-port-synth
 */

#ifndef GLOBAL_PARAMETERS_H
#define GLOBAL_PARAMETERS_H    

#define KNOB_DIVISOR 1000.0
#define KNOB_STEP 10

//GAIN
#define GAIN_MIN 0
#define GAIN_MAX 1000
#define GAIN_DEFAULT 200

//OSCILLATOR_MIX
#define OSCILLATOR_MIX_MIN 0
#define OSCILLATOR_MIX_MAX 1000
#define OSCILLATOR_MIX_DEFAULT 500

//ENVELOPE ATTACK TIME
#define ENV_ATTACK_TIME_MIN 10
#define ENV_ATTACK_TIME_MAX 990
#define ENV_ATTACK_TIME_DEFAULT 500

//ENVELOPE RELEASE TIME
#define ENV_RELEASE_TIME_MIN 10
#define ENV_RELEASE_TIME_MAX 2000
#define ENV_RELEASE_TIME_DEFAULT 500

//ENVELOPE DECAY TIME
#define ENV_DECAY_TIME_MIN 10
#define ENV_DECAY_TIME_MAX 990
#define ENV_DECAY_TIME_DEFAULT 500

//ENVELOPE SUSTAIN AMPLITUDE
#define ENV_SUSTAIN_AMPL_MIN 0
#define ENV_SUSTAIN_AMPL_MAX 1000
#define ENV_SUSTAIN_AMPL_DEFAULT 1000

//FILTER ENVELOPE ATTACK TIME
#define FILTER_ENV_ATTACK_TIME_MIN 10
#define FILTER_ENV_ATTACK_TIME_MAX 990
#define FILTER_ENV_ATTACK_TIME_DEFAULT 500

//FILTER ENVELOPE RELEASE TIME
#define FILTER_ENV_RELEASE_TIME_MIN 10
#define FILTER_ENV_RELEASE_TIME_MAX 2000
#define FILTER_ENV_RELEASE_TIME_DEFAULT 500

//FILTER ENVELOPE DECAY TIME
#define FILTER_ENV_DECAY_TIME_MIN 10
#define FILTER_ENV_DECAY_TIME_MAX 990
#define FILTER_ENV_DECAY_TIME_DEFAULT 500

//FILTER ENVELOPE SUSTAIN AMPLITUDE
#define FILTER_ENV_SUSTAIN_AMPL_MIN 0
#define FILTER_ENV_SUSTAIN_AMPL_MAX 1000
#define FILTER_ENV_SUSTAIN_AMPL_DEFAULT 1000

//FILTER RESONANCE
#define FILTER_RESONANCE_MIN 1
#define FILTER_RESONANCE_MAX 990
#define FILTER_RESONANCE_DEFAULT 1

//FILTER CUTOFF
#define FILTER_CUTOFF_MIN 1
#define FILTER_CUTOFF_MAX 990
#define FILTER_CUTOFF_DEFAULT 990

//LFO FREQUENCY
#define LFO_FREQUENCY_MIN 0
#define LFO_FREQUENCY_MAX 20000
#define LFO_FREQUENCY_DEFAULT 0

//LFO AMOUNT
#define LFO_AMOUNT_MIN 0
#define LFO_AMOUNT_MAX 1000
#define LFO_AMOUNT_DEFAULT 0

#endif