
#include <iostream>

#include "person.hpp"

using namespace std;

Person::Person() : roll(0.0), pitch(0.0), yaw(0.0) {}

Person::Person(float r, float p, float y) {
	roll = r;
	pitch = p;
	yaw = y;
}

Person::~Person() {}

string Person::toString() {
	return ("Roll : " + to_string(roll) + " Pitch : " + to_string(pitch) + " Yaw : " + to_string(yaw) + "\n");
}
