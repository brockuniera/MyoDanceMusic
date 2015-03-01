
#include "person.hpp"
#include "CircularBuffer.hpp"
#include <vector>

class Song {
	public:
		
		float intensity;
		int beats_per_minute = 120;
		std::vector<Person> people;
		int people_size = people.size();
		CircularBuffer yaw(people_size * 10);
		CircularBuffer roll(people_size * 10);
		CircularBuffer pitch(people_size * 10);

		Song();
		Song(std::vector<Person>&);
		~Song();
		// void update(std::vector<Person>&);
		void update(void);
};

