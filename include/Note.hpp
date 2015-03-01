#ifndef __NOTE__HPP__
#define __NOTE__HPP__

//This class knows what scale its in, and it's increment values align to scale 

class Note{
	private:
		char _noteInternal; //maps directly to midi
									 //so far, this could be destroyed if we mess up...
		int _scalePos; //where note is on scale

		void moveScaleNote(int);
	public:
		static const int dorianScale[7];  //scale vals

		Note();

		char getNote(void);
		int getScalePos(void);
		void reset(void);

		Note& operator+=(int rhs);
		Note& operator-=(int rhs);

		Note& operator++();
		Note& operator--();
};

#endif
