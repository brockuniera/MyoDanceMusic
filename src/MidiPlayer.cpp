#include "MidiPlayer.hpp"

#define NOTE_ON 144
#define NOTE_OFF 128
#define DEF_VELOCITY 100

MidiPlayer &MidiPlayer::getInstance(){
	static MidiPlayer instance;
	return instance;
}

void MidiPlayer::stopNotes(void){
	//iterate through, decrease length by one...
	//remove and turn note off if 0
	for(auto it = _notesToStop.begin(); it != _notesToStop.end(); it++){
		if(--(it->second.second) <= 0){
			//turn note off...
			_message[0] = NOTE_OFF + it->second.first; //"Note Off" + channel
			_message[1] = it->first;
			_message[2] = 0;	

			//...output midi message
			_midiout->sendMessage(&_message);

			//remove from map
			_notesToStop.erase(it);
		}
	}

}

void MidiPlayer::playNote(Note note, unsigned int channel, unsigned int length){		
	if(note < 0){
		std::cout << "Note is out of range (0 - 127)" << std::endl;
		return;
	}
	if(channel > 15){
		std::cout << "Channel is out of range (0 - 15)" << std::endl;
		return;
	}

	_message[0] = NOTE_ON + channel; //"Note On" + channel
	_message[1] = note;
	_message[2] = DEF_VELOCITY;	

	//output midi
	_midiout->sendMessage(&_message);

	//insert to map...
	auto p = _notesToStop.insert(std::make_pair(note, std::make_pair(channel, length)));
	if(p.second == false){ //a note was already here!!
		//so we will reset it's length
		(p.first)->second.second = length;
	}

}

MidiPlayer::MidiPlayer(){
	//RtMidiOut needs to be constructed in try/catch block
	try{
		_midiout = new RtMidiOut();
		_midiout->openVirtualPort();
	}
	catch (RtMidiError &error) {
		std::cout << "Couldn't instantiate!!!" << std::endl;
		error.printMessage();
		return;
	}

	//_message should be at least size 3
	//_message.reserve(3);
	_message.push_back(0);
	_message.push_back(0);
	_message.push_back(0);

}
MidiPlayer::~MidiPlayer(){
	//_midiout wasn't guarunteed to be created... :(
	if(_midiout == NULL)
		delete _midiout;
}

