
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

		unsigned int timer;

		unsigned char channel;
	public:
		Person(unsigned char chnl);

		~Person();

		float roll, pitch, yaw;

		//cool member functions
		void setData(float, float, float);
		void playNotes(void);
		string toString();

		bool hasStarted = false;
};

#endif
