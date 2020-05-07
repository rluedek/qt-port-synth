/**
 * @file MidiIn.h
 * @author rico luedeke
 * @brief Wrapper class around rtmidi. Allows event bases midi event catching.
 * @see https://www.music.mcgill.ca/~gary/rtmidi/ for further information about rtmidi
 * @date 2020-03-29
 * 
 * @copyright Copyright (c) 2020 - This code is licensed under MIT license (see LICENSE.txt for details)
 */

#ifndef RL_MIDI_MIDI_IN
#define RL_MIDI_MIDI_IN

#include "RtMidi.h"
#include "MidiDevice.h"
#include "IMidiInputListener.h"

#include <iostream>
#include <stdint.h>
#include <memory>
#include <thread>

namespace midi
{
    class MidiIn
    {
    public:
        
        //ctor
        MidiIn();

        //dtor
        virtual ~MidiIn();

        /**
         * @brief Start a monitoring thread. Sends events to @class{IMidiInputLister}
         * 
         * @param midiPort The port to listen on.
         * @param midiChannel The midi channel to listen on (default: MIDICHANEL_ALL)
         * @return true 
         * @return false 
         */
        bool runMonitoring(int midiPort, int midiChannel);

        /**
         * @brief Stop the current monitoring thread, if running.
         * 
         */
        void stopMonitoring();

        void listDevices(std::vector<MidiDevice>& midiDevices);

        /**
         * @brief Set the Input Listener object
         * 
         * @param pInputListener The registered @class{MidiInputListener}
         */
        void setInputListener(std::shared_ptr<IMidiInputListener> pInputListener);
    
    private:
        
        bool                                m_bRunning;
        unsigned int                        m_midiChannel;
        unsigned int                        m_midiPort;

        std::shared_ptr<std::thread>        m_pMonitorThread;
        std::shared_ptr<RtMidiIn>           m_pRtMidiIn;
        std::shared_ptr<IMidiInputListener> m_pInputListener;

        /**
         * @brief Thread function that periodically check for new midi events
         * 
         */
        void monitor();
        std::shared_ptr<RtMidiIn> getInstance();

    };
}

#endif
