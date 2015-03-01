
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
		//Internal state
		//TODO replace w/ ring buffer or something
		float roll, pitch, yaw;
		
		//TODO probably remove
		unsigned int timer;

		unsigned char channel;
	public:
		Person(unsigned char chnl);

		~Person();

		//cool member functions
		void setData(float, float, float);
		void playNotes(void);
		string toString();
		float getRoll();
		float getPitch();
		float getYaw();

		bool hasStarted = false;
};

#endif
