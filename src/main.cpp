#include <iostream>
#include <unistd.h> //usleep, microsleep
#include "MidiPlayer.hpp"

int main(){
	//Lets say, 120bpm
	unsigned int microsPer16th = 125000;
	MidiPlayer& mp = MidiPlayer::getInstance();
	sleep(1);

	while(1){
		//should play a 16th note at 120bpm
		mp.playNote(67, 0, 1);
		mp.stopNotes();
		usleep(microsPer16th);
	}
}
