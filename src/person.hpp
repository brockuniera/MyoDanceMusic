
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

using namespace std;

class Person {
	public:
		float roll, pitch, yaw;
		Person();
		Person(float,float,float);
		~Person();

		string toString();
};


#endif
