/**
 * @file MidiReceiver.h
 * @author rico luedeke
 * @date 2020-03-29
 * @see IMidiInputListener
 * 
  * @copyright Copyright (c) 2020
 */
#ifndef MIDI_RECEIVER
#define MIDI_RECEIVER

#include "midi/IMidiInputListener.h"

#include "audio/Audio.h"

class MidiReceiver : public midi::IMidiInputListener
{
public:

    //ctor
    MidiReceiver(AudioHal& audio);

    void onNoteOn(int keyNumber, int velocity, int midiChannel);

    void onNoteOff(int keyNumber, int velocity, int midiChannel);

    void onMidiEvent(std::vector<unsigned char> bytes);    

private:

    AudioHal& m_audio;

    static double keyNumberToFrequency(unsigned keynumber)
    {
        return 440.0 * pow(2.0, (keynumber - 69.0) / 12.0);
    } 

};

#endif
