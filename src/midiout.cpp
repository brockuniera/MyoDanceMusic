#include <iostream>
#include <cstdlib>
#include "RtMidi.h"

// Platform-dependent sleep routines.
#if defined(__WINDOWS_MM__)
#include <windows.h>
#define SLEEP(milliseconds) Sleep((DWORD) milliseconds) 
#else // Unix variants
#include <unistd.h>
#define SLEEP(milliseconds) usleep((unsigned long) (milliseconds * 1000.0))
#endif

#define CLOCK_TIME 27

// This function should be embedded in a try/catch block in case of
// an exception.  It offers the user a choice of MIDI ports to open.
// It returns false if there are no ports available.
bool chooseMidiPort(RtMidiOut *rtmidi);

int main(void)
{

	// Place to store user input
	std::string keyHit;

	// Makes output midi things
	RtMidiOut *midiout = NULL;

	// vector for our usually 3 byte message
	std::vector<unsigned char> message;

	// RtMidiOut constructor
	try {
		midiout = new RtMidiOut();
	}
	catch (RtMidiError &error) {
		error.printMessage();
		exit(EXIT_FAILURE);
	}

	// Call function to select port.
	try {
		if (chooseMidiPort(midiout) == false) goto cleanup;
	}
	catch (RtMidiError &error) {
		error.printMessage();
		goto cleanup;
	}

	// Put three things in our message vector
	message.push_back(0);
	message.push_back(0);
	message.push_back(0);


	//
	// Send out a series of MIDI messages. Forever.
	//

	std::cout << "Sending infinite notes to two different channels" << std::endl;
	std::cout << "Input q to quit" << std::endl;

	do{
		//Channel 1 Note On: 144, 64, 90
		message[0] = 144; //channel command
		message[1] = 64;  //note
		message[2] = 90;  //velocity
		midiout->sendMessage(&message);

		SLEEP(500);

		// Channel 1 Note Off: 128, 64, 40
		message[0] = 128;
		message[1] = 64;
		message[2] = 40;
		midiout->sendMessage(&message);

		//puts("Wait...");
		//SLEEP(1000);
		//puts("...Now!");

		//for(int i = 0; i < 5; i++){
			////test control buttons
			////on
			//message[0] = 191;
			//message[1] = 117;
			//message[2] = 127;
			//midiout->sendMessage(&message);

			//SLEEP(500);

			////off
			//message[0] = 191;
			//message[1] = 117;
			//message[2] = 127;
			//midiout->sendMessage(&message);
		//}
		std::getline(std::cin, keyHit);
	}while(keyHit != "q");
	
	//while(1){
		//message[0] = 248;
		//midiout->sendMessage(&message);
		//SLEEP(CLOCK_TIME);
	//}



	// Clean up
cleanup:
	delete midiout;

	return 0;
}

bool chooseMidiPort(RtMidiOut *rtmidi)
{
	std::cout << "\nWould you like to open a virtual output port? [y/N] ";

	std::string keyHit;
	std::getline(std::cin, keyHit);
	if (keyHit == "y") {
		rtmidi->openVirtualPort();
		return true;
	}

	std::string portName;
	unsigned int i = 0, nPorts = rtmidi->getPortCount();
	if (nPorts == 0) {
		std::cout << "No output ports available!" << std::endl;
		return false;
	}

	if (nPorts == 1) {
		std::cout << "\nOpening " << rtmidi->getPortName() << std::endl;
	}
	else {
		for (i=0; i<nPorts; i++) {
			portName = rtmidi->getPortName(i);
			std::cout << "  Output port #" << i << ": " << portName << '\n';
		}

		do {
			std::cout << "\nChoose a port number: ";
			std::cin >> i;
		} while (i >= nPorts);
	}

	std::cout << "\n";
	rtmidi->openPort(i);

	return true;
}
