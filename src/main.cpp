#include <iostream>
#include <unistd.h> //usleep, microsleep
#include "MidiPlayer.hpp"

int main(){
	//Lets say, 120bpm
	unsigned int microsPer16th = 125000;
	MidiPlayer& mp = MidiPlayer::getInstance();
	sleep(1);

		usleep(microsPer16th);
	}
}
