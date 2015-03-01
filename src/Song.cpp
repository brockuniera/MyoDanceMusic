
#include "Song.hpp"

Song::Song() {
	intensity = 0.0;
	yaw.setSlots(people->size() * 10);
	roll.setSlots(people->size() * 10);
	pitch.setSlots(people->size() * 10);
}

Song::Song(std::vector<Person>* ppl) {
	people = ppl;
	intensity = 0.0;
	yaw.setSlots(people->size() * 10);
	roll.setSlots(people->size() * 10);
	pitch.setSlots(people->size() * 10);
}

void Song::update(void) {
	for (unsigned int i = 0; i < people->size(); i++) {
		roll.write(people->at(i).roll);
		pitch.write(people->at(i).pitch);
		yaw.write(people->at(i).yaw);
	}

	float rollDerivative = roll.findDerivative();
	float pitchDerivative = pitch.findDerivative();
	float yawDerivative = yaw.findDerivative();

	intensity = ((rollDerivative + pitchDerivative + yawDerivative)/3);

	cout << "Song intensity: " << intensity << endl;
	
}
