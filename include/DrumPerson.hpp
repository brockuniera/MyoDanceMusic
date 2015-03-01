
#ifndef _DRUM_PERSON_HPP
#define _DRUM_PERSON_HPP

#include <myo/myo.hpp>

#include "Note.hpp"
#include "MidiPlayer.hpp"
#include "person.hpp"

class DrumPerson : Person{
	public:
		virtual void playNotes(void) override;
};

#endif
