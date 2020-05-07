/**
 * @file IMidiInputListener.h
 * @author rico luedeke
 * @brief Midi listener that can be derived from any class that wants to
 * have midi event callbacks
 * @date 2020-03-29
 *
 * @copyright Copyright (c) 2020 - This code is licensed under MIT license (see LICENSE.txt for details)

 */

#ifndef RL_MIDI_IMIDI_INPUTLISTENER
#define RL_MIDI_IMIDI_INPUTLISTENER

#include <vector>

namespace midi
{
    class IMidiInputListener
    {
    public:
    /**
     * @brief Is called in case of a new midi NOTEON event
     * 
     * @param keyNumber The number of the currently pressed note
     * @param velocity The (press) velocity of the note
     * @param midiChannel The midi channel the event has been sent
     */
        virtual void onNoteOn(int keyNumber, int velocity, int midiChannel) = 0;
    
    /**
     * @brief Is called whenever a note has been released
     * 
     * @param keyNumber The number of the currently released note
     * @param velocity The (release) velocity of the note
     * @param midiChannel The midi channel the event has been sent
     */
        virtual void onNoteOff(int keyNumber, int velocity, int midiChannel) = 0;
    
    /**
     * @brief Gets called every time when a midi event cannot be identified as 
     * NOTEON or NOTEOFF event
     * 
     * @param bytes The message of the midi event
     * @see https://de.wikipedia.org/wiki/Musical_Instrument_Digital_Interface for description
     */
        virtual void onMidiEvent(std::vector<unsigned char> bytes) = 0;
    };
}

#endif
