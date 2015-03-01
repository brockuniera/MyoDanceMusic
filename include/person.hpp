
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
//#include "CircularBuffer.hpp"

using namespace std;

class Person {
	private:
		MidiPlayer& mp;

		//Internal state
		//TODO replace w/ ring buffer or something
		float roll, pitch, yaw;
		
		unsigned int timer;

		unsigned char channel;

		//CircularBuffer cb<float>(); //Doesnt exist yet
	public:
		Person(unsigned char chnl);

		~Person();

		//cool member functions
		void setData(float, float, float);
		virtual void playNotes(void);
		string toString();
};

#endif
