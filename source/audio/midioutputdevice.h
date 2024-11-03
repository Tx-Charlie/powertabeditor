/*
  * Copyright (C) 2011 Cameron White
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
  
#ifndef AUDIO_MIDIOUTPUTDEVICE_H
#define AUDIO_MIDIOUTPUTDEVICE_H

/**
// MIDI control change:
// first parameter is 0xB0-0xBF with B being the id and 0-F being the channel (0-15)
// second parameter is the control to change (0-127), (e.g. 7 is channel volume)
// third parameter is the new value (0-127)
**/

#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <vector>
#include <score/generalmidi.h>

class RtMidiOut;

class MidiOutputDevice
{
public:
    MidiOutputDevice();
    ~MidiOutputDevice();

    bool initialize(const std::string_view &preferred_api,
                    const std::string_view &preferred_port);
    size_t getApiCount();
    std::string getApiName(size_t api);
    unsigned int getPortCount(size_t api);
    std::string getPortName(size_t api, unsigned int port);

    /// Sets the pitch bend range to the given number of semitones.
    void setPitchBendRange(int channel, uint8_t semiTones);
    bool setPatch(int channel, uint8_t patch);
    bool setVolume(int channel, uint8_t volume);
    bool setPan(int channel, uint8_t pan);
    bool setPitchBend(int channel, uint16_t bend);
    bool playNote(int channel, uint8_t pitch, uint8_t velocity);
    bool stopNote(int channel, uint8_t pitch);
    bool setVibrato(int channel, uint8_t modulation);
    /// Turns sustain on or off for the specified channel.
    bool setSustain(int channel, bool sustainOn);

    /// Set the upper limit on a channel's volume. The volume can then be
    /// adjusted within that range by dynamic symbols.
    void setChannelMaxVolume(int channel, uint8_t maxVolume);

    enum MidiMessage
    {
        NoteOff = 128,
        NoteOn = 144,
        ControlChange = 176,
        ProgramChange = 192,
        PitchWheel = 224
    };

    enum ControlChanges
    {
        ModWheel = 1,
        DataEntryCoarse = 6,
        ChannelVolume = 7,
        PanChange = 10,
        DataEntryFine = 38,
        HoldPedal = 64,
        RpnLsb = 100,
        RpnMsb = 101,
        AllNotesOff = 123
    };

    void sendMessage(const std::vector<uint8_t> &data);

    // Stops notes on all channels. Useful if playback was interrupted.
    void stopAllNotes();

private:
    bool sendMidiMessage(unsigned char a, unsigned char b, unsigned char c);

    std::vector<std::unique_ptr<RtMidiOut>> myMidiOuts;
    RtMidiOut *myMidiOut;
    /// Maximum volume for each channel (as set in the mixer).
    std::array<uint8_t, Midi::NUM_MIDI_CHANNELS_PER_PORT> myMaxVolumes;
    /// Volume of last active dynamic for each channel.
    std::array<uint8_t, Midi::NUM_MIDI_CHANNELS_PER_PORT> myActiveVolumes;
};

#endif
