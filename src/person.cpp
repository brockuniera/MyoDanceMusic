
#include "Person.hpp"

using namespace std;

Person::Person(unsigned char chnl) : mp(MidiPlayer::getInstance()), channel(chnl){
	timer = 4;
}

Person::~Person() {}

void Person::setData(float r, float p, float y) {
	roll = r;
	pitch = p;
	yaw = y;
}

float getRoll() {
	return roll;
}

float getPitch() {
	return pitch;
}

float getYaw() {
	return yaw;
}

void Person::playNotes(void){
	//TODO
	if(channel == 1)
		cout << pitch << "\t" << yaw << "\t" << roll << endl;

	timer--;
	if(timer != 0){
		return;
	}
	timer = 2; //reset

	//TODO
	//algorithms and shit go here

	int note = (pitch/4) + 50; 

	//cout << "Person " << (int)channel << " note is :" << note << endl;

	mp.playNote(note, channel, 1);

}

string Person::toString() {
	return ("Roll : " + to_string(roll) + " Pitch : " + to_string(pitch) + " Yaw : " + to_string(yaw) + "\n");
}

