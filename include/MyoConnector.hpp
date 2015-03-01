#ifndef __MYO_CONNECTER_HPP__
#define __MYO_CONNECTER_HPP__

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <map>
#include <typeinfo>
#include <utility>
#include <myo/myo.hpp>
#include "Person.hpp"

using namespace myo;
using namespace std;

class DataCollector : public DeviceListener {
	private:
		//maps things
		map<Myo*, Person*> myomap;

		//iterators
		vector<Person>::iterator nextPerson;
		vector<Person>::iterator peopleEnd;

		//XXX Do we care??
		//Pose currentPose;
		//Arm whichArm;

	public:
		DataCollector(vector<Person>::iterator begin, vector<Person>::iterator end);
		void onPair(Myo* myo, uint64_t timestamp, FirmwareVersion firmwareVersion);
		void onUnpair(Myo* myo, uint64_t timestamp);
		void onOrientationData(Myo* myo, uint64_t timestamp, const Quaternion<float>& quat);

		//void onPose(Myo* myo, uint64_t timestamp, Pose pose);
		//void onArmSync(Myo* myo, uint64_t timestamp, Arm arm, XDirection xDirection);
		//void onArmUnsync(Myo* myo, uint64_t timestamp);
		//void onUnlock(Myo* myo, uint64_t timestamp);
		//void onLock(Myo* myo, uint64_t timestamp);
};

#endif
