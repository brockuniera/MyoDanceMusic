
#include "Song.hpp"

Song::Song() {
	intensity = 0.0;
}

Song::Song(std::vector<Person>& ppl) {
	&people = ppl;
}

void Song::update(void) {
	for (int i = 0; i < ppl.size(); i++) {
		roll.write(ppl[i].getRoll());
		pitch.write(ppl[i].getPitch());
		yaw.write(ppl[i].getYaw());
	}

	float rollDerivative = roll.getDerivative();
	float pitchDerivative = pitch.getDerivative();
	float yawDerivative = yaw.getDerivative();

	intensity = ((rollDerivative + pitchDerivative + yawDerivative)/3);
}
