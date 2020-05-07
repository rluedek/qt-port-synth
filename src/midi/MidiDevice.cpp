/**
 * @file MidiDevice.cpp
 * @author rico luedeke
 * @brief A class for holding information about a midi device
 * @date 2020-03-30
 * 
 * @copyright Copyright (c) 2020 - This code is licensed under MIT license (see LICENSE.txt for details)
 */

#include "MidiDevice.h"

namespace midi
{
    MidiDevice::MidiDevice(std::string portName, unsigned int portNumber)
    : m_portName(portName)
    , m_portNumber(portNumber)
    {

    }

    std::string MidiDevice::getPortName()
    {
        return m_portName;
    }
    
    unsigned int MidiDevice::getPortNumber()
    {
        return m_portNumber;
    }
}
