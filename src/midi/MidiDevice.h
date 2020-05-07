/**
 * @file MidiDevice.h
 * @author rico luedeke
 * @brief A class for holding information about a midi device
 * @date 2020-03-30
 * 
 * @copyright Copyright (c) 2020 - This code is licensed under MIT license (see LICENSE.txt for details)
 */

#ifndef RL_MIDI_DEVICE
#define RL_MIDI_DEVICE

#include "RtMidi.h"

#include <iostream>
#include <stdint.h>

namespace midi
{
    class MidiDevice
    {
    public:
        
        //ctor
        MidiDevice(std::string portName, unsigned int portNumber);

        /**
         * @brief Get the Port Name object of this device
         * 
         * @return std::string 
         */
        std::string getPortName();

        /**
         * @brief Get the Port Number object of this device
         * 
         * @return unsigned int 
         */
        unsigned int getPortNumber();
    
    private:
        
        std::string m_portName;
        unsigned int m_portNumber;
    };
}

#endif
