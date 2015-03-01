
#include "Person.hpp"

using namespace std;

Person::Person(unsigned char chnl) : mp(MidiPlayer::getInstance()), channel(chnl){
	timer = 0;
}

Person::~Person() {}

void Person::setData(float r, float p, float y) {
	roll = r;
	pitch = p;
	yaw = y;
}

void Person::playNotes(void){
	//timer++;
	//if(timer == 15){
		//timer = 0;
	//}else{
		//return;
	//}

	//TODO
	//algorithms and shit go here

	int note = (pitch/2) + 30; 

	cout << "Person " << (int)channel << " note is :" << note << endl;

	mp.playNote(note, channel, 4);
}

string Person::toString() {
	return ("Roll : " + to_string(roll) + " Pitch : " + to_string(pitch) + " Yaw : " + to_string(yaw) + "\n");
}

