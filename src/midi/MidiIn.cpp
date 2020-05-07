/**
 * @file MidiIn.cpp
 * @author rico luedeke
 * @see MidiIn.h
 * @date 2020-03-29
 * 
 * @copyright Copyright (c) 2020 - This code is licensed under MIT license (see LICENSE.txt for details)
 */

#include "MidiIn.h"
#include "MidiChannelSelection.h"

#include <unistd.h> // usleep

#define NOTEON          144
#define NOTEOFF         128
#define NOTEMASK        240
#define CHANNELMASK     15

namespace midi
{
    MidiIn::MidiIn()
    : m_bRunning(false)
    {
        try
        {
            m_pRtMidiIn = std::make_shared<RtMidiIn>();
        }
        catch(RtMidiError& error)
        {
            error.printMessage();
        }
    }

//--------------------------------------------------------------------------------
    
    MidiIn::~MidiIn()
    {
        stopMonitoring();
    }

//--------------------------------------------------------------------------------

    bool MidiIn::runMonitoring(int midiPort, int midiChannel = MIDICHANNEL_ALL)
    {
        if(m_bRunning)
        {
            stopMonitoring();
        }

        m_midiChannel = midiChannel;
        m_midiPort = midiPort;

        try
        {
            m_pRtMidiIn->openPort(midiPort);
        
            // Don't ignore sysex, timing, or active sensing messages.
            m_pRtMidiIn->ignoreTypes(false, false, false);
        
            m_bRunning = true;
            
            m_pMonitorThread = std::make_shared<std::thread>(&MidiIn::monitor, this);

        }
        catch (RtMidiError &error)
        {
            return false;
        }

        return true;
    }

//--------------------------------------------------------------------------------

    void MidiIn::stopMonitoring()
    {
        m_bRunning = false;

        if (m_pMonitorThread)
        {
            m_pMonitorThread->join();
        }
    }

//--------------------------------------------------------------------------------

    void MidiIn::listDevices(std::vector<MidiDevice>& midiDevices)
    {
        midiDevices.clear();

        if (m_pRtMidiIn)
        {
            unsigned int nPorts = m_pRtMidiIn->getPortCount();
            std::string portName;
            for (unsigned int i = 0; i < nPorts; i++)
            {
                try
                {
                    portName = m_pRtMidiIn->getPortName(i);
                    midiDevices.push_back(MidiDevice(portName, i));
                }
                catch (RtMidiError &error)
                {
                    error.printMessage();
                }
            }
        }
    }

//--------------------------------------------------------------------------------

    void MidiIn::setInputListener(std::shared_ptr<IMidiInputListener> pInputListener)
    {
        m_pInputListener = pInputListener;
    }

//--------------------------------------------------------------------------------

    void MidiIn::monitor()
    {
        std::vector<unsigned char> message;
        int noteNumber, velocity, midiChannel, action, byte1;
        double stamp;

        while (m_bRunning)
        {
            if (m_pInputListener)
            {
                stamp = m_pRtMidiIn->getMessage(&message);

                if (message.size() > 0)
                {
                    byte1 = (int)message[0];
                    action = byte1 & NOTEMASK;

                    if (action == NOTEON || action == NOTEOFF)
                    {
                        noteNumber = (int)message[1]; 
                        velocity = (int)message[2];
                        midiChannel =  (byte1 & CHANNELMASK) + 1;

                        if (m_midiChannel == MIDICHANNEL_ALL 
                            || midiChannel == m_midiChannel)
                        {

                            if (action == NOTEON)
                                m_pInputListener->onNoteOn(noteNumber
                                                            , velocity
                                                            , midiChannel);
                            else                    
                                m_pInputListener->onNoteOff(noteNumber
                                                            , velocity
                                                            , midiChannel);
                        }
                    }
                    else // handle all the other midi events
                    {
                        m_pInputListener->onMidiEvent(message);         
                    }   
                }         
            }
            usleep(10000);
        }

        m_pRtMidiIn->closePort();
    }
}
