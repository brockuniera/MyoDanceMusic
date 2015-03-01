#ifndef __MIDIPLAYER_HPP
#define __MIDIPLAYER_HPP

#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <utility> //std::pair<>
#include "RtMidi.h"

// Midi notes range from 0 to 127

/*
 * Plays midi notes for a specified time 
 * Singleton, only one RtMidiOut needs to exist 
 */
class MidiPlayer{
	public:
		//Singleton
		static MidiPlayer& getInstance();

		// Needs to be called every tick, to tell notes when to stop
		// Ideally, called before playNote()
		void stopNotes(void);

		//Plays note for specified length, in whatever currents ticks are
		void playNote(char n, unsigned int channel, unsigned int length);

	private:
		//Play notes through this
		RtMidiOut* _midiout;

		//small buffer to hold midi messages
		std::vector<unsigned char> _message;

		//holds notes that need to eventually end
		// Note -> <channel, length>
		std::map<char, std::pair<unsigned int, unsigned int> > _notesToStop;

		MidiPlayer();
		~MidiPlayer();

		//don't let these functions get defined in a singleton pattern
		MidiPlayer(MidiPlayer const&);
		void operator=(MidiPlayer const&);
};

#endif
