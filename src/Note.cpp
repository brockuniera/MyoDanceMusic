#include "Note.hpp"

//Note should start at middle c, scale pos is at 0
Note::Note(){
	reset();
}

const int Note::dorianScale[7] = {2, 2, 1, 2, 2, 2, 1};

char Note::getNote(void){
	return _noteInternal;
}

int Note::getScalePos(void){
	return _scalePos;
}

void Note::moveScaleNote(int dltpos){
	int sign = 1;
	if(dltpos < 0){
		sign = -sign;
		dltpos = -dltpos;
	}

	while(dltpos--){
		//move note internal correctly
		_noteInternal += sign * Note::dorianScale[_scalePos];
		_scalePos += sign;

		//loop around
		if(_scalePos == 7)
			_scalePos = 0;
		else if(_scalePos == -1)
			_scalePos = 6;

	}
}

void Note::reset(void){
	_noteInternal = 60;
	_scalePos = 0;
}

Note& Note::operator+=(int rhs){
	this->moveScaleNote(rhs);
	return *this;
}
Note& Note::operator-=(int rhs){
	this->moveScaleNote(-rhs);
	return *this;
}

Note& Note::operator++(){
	this->moveScaleNote(1);
	return *this;
}
Note& Note::operator--(){
	this->moveScaleNote(-1);
	return *this;
}

