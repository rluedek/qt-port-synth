/**
 * @file MidiReceiver.cpp
 * @author rico luedeke
 * @see MidiReceiver.h
 * @date 2020-03-29
 * 
 * 
 * @copyright Copyright (c) 2020
* */

#include "MidiReceiver.h"

#include <iostream> // cout

MidiReceiver::MidiReceiver(AudioHal& audio)
: m_audio(audio)
{
    
}

void MidiReceiver::onNoteOn(int keyNumber, int velocity, int midiChannel)
{
    m_audio.play(keyNumberToFrequency(keyNumber));

    std::cout   << "MidiReceiver::onNoteOn: keyNumber " << keyNumber 
                << " velocity: " << velocity 
                << " channel: " << midiChannel 
                << std::endl;
}

void MidiReceiver::onNoteOff(int keyNumber, int velocity, int midiChannel)
{
  m_audio.stop(keyNumberToFrequency(keyNumber));
    std::cout   << "MidiReceiver::onNoteOff: keyNumber " << keyNumber 
                << " velocity: " << velocity 
                << " channel: " << midiChannel 
                << std::endl;
}

void MidiReceiver::onMidiEvent(std::vector<unsigned char> bytes)
{
  //Do nothing right now
   /*
    std::cout << "MidiReceiver::onMidiEvent: ";

    for ( int i = 0; i < bytes.size(); i++ )
      std::cout << "Byte " << i << " = " << (int)bytes[i] << ", ";

    std::cout << std::endl;
    */   
}
