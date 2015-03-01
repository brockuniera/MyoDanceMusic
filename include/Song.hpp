
#include "person.hpp"
#include "CircularBuffer.hpp"
#include <vector>

class Song {
	public:
		float intensity;
		int beats_per_minute = 120;
		std::vector<Person> people;
		CircularBuffer yaw;
		CircularBuffer roll;
		CircularBuffer pitch;

		Song();
		Song(std::vector<Person>);
		// void update(std::vector<Person>&);
		void update(void);
};
