#ifndef _ALGO_HPP
#define _ALGO_HPP
#define _USE_MATH_DEFINES
#include "person.hpp"
#include "MidiPlayer.hpp"
#include <vector>
#include <algorithm>


class Algo{
	public:
		std::vector<int> ringbuffer;
		std::vector<int> pastNotes;
		unsigned int bpm=120;
		std::vector<int> curr_chord;
		MidiPlayer mp = MidiPlayer.getInstance();
		//std::vector<int> chords;
		//void (alg*)(std::vector<person>);

		virtual void random_alg(std::vector<person>);		//gaussian weighted
		void no_alg(std::vector<Person>);					//all movement maps to some note
		virtual void instruments(std::vector<person>);		//each channel is a different instrument
		void ayk_alg(std::vector<Person>);					//badass default alg.
		
	private:
		void normalize(unsigned int note);
};

#endif
