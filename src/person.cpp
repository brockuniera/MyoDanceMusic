
#include "Person.hpp"

using namespace std;

Person::Person(unsigned char chnl) : mp(MidiPlayer::getInstance()), channel(chnl){
	timer = 8;
}

Person::~Person() {}

void Person::setData(float r, float p, float y) {
	roll = r;
	pitch = p;
	yaw = y;
}

void Person::playNotes(void){
	--timer;
	cout << "Timer " << timer << endl;
	if(timer != 0){
		return;
	}
	timer = 5; //reset

	//TODO
	//algorithms and shit go here

	int note = (pitch/2) + 30; 

	cout << "Person " << (int)channel << " note is :" << note << endl;

	mp.playNote(note, channel, 1);

}

string Person::toString() {
	return ("Roll : " + to_string(roll) + " Pitch : " + to_string(pitch) + " Yaw : " + to_string(yaw) + "\n");
}

