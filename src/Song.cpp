
#include "Song.hpp"

Song::Song() {
	intensity = 0.0;
	yaw.setSlots(people.size() * 10);
	roll.setSlots(people.size() * 10);
	pitch.setSlots(people.size() * 10);
}

Song::Song(std::vector<Person> ppl) {
	people = ppl;
	intensity = 0.0;
	yaw.setSlots(people.size() * 10);
	roll.setSlots(people.size() * 10);
	pitch.setSlots(people.size() * 10);
}

void Song::update(void) {
	for (int i = 0; i < people.size(); i++) {
		roll.write(people[i].getRoll());
		pitch.write(people[i].getPitch());
		yaw.write(people[i].getYaw());
	}

	float rollDerivative = roll.findDerivative();
	float pitchDerivative = pitch.findDerivative();
	float yawDerivative = yaw.findDerivative();

	intensity = ((rollDerivative + pitchDerivative + yawDerivative)/3);

	
}
