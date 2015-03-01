
#include "person.hpp"
#include "CircularBuffer.hpp"
#include "person.hpp"

class Song {
	public:
		CircularBuffer yaws(10);
		CircularBuffer roll(10);
		CircularBuffer pitch(10);
		float intensity;
		vector<Person> persons;


};

