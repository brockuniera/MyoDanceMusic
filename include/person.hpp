
#ifndef _PERSON_HPP
#define _PERSON_HPP

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <myo/myo.hpp>
#include "MidiPlayer.hpp"

using namespace std;

class Person {
	private:
		MidiPlayer& mp;

		//Internal state
		//TODO replace w/ ring buffer or something
		float roll, pitch, yaw;
		
		//TODO probably remove
		int timer;

		unsigned char channel;
	public:
		Person(unsigned char chnl);

		~Person();

		//cool member functions
		void setData(float, float, float);
		void playNotes(void);
		string toString();

		bool hasStarted = false;
};

#endif
