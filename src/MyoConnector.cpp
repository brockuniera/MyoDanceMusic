
#include "MyoConnector.hpp"
#define RAD_TO_ANGLE 180.0/3.14159

using namespace std;
using namespace myo;

DataCollector::DataCollector(vector<Person>& ppl) : peoples(ppl) {}

void DataCollector::onPair(Myo* myo, uint64_t timestamp, FirmwareVersion firmwareVersion) {
	cout << "A Myo connected!" << endl;
	
	peoples.push_back(Person(peoples.size()));

	myomap[myo] = &(peoples.back());
	// myomap[myo]->hasStarted = true;
}

void DataCollector::onUnpair(Myo* myo, uint64_t timestamp) {
	cout << "Myo unpaired!" << endl;
	vector<Person>::iterator iter;
	for(iter = peoples.begin(); iter != peoples.end(); iter++) {
		if (&(*iter) == myomap[myo]) {
			peoples.erase(iter);
		}
	}

//	int positionToRemove = find(peoples.begin(), peoples.end(), *myomap[myo]) - peoples.begin();
//	peoples.erase(peoples.begin() + positionToRemove);
	
	// myomap[myo]->hasStarted = false;
	myomap.erase(myo);
}

// onOrientationData() is called whenever the Myo device provides its current orientation, which is represented
// as a unit quaternion.
void DataCollector::onOrientationData(Myo* myo, uint64_t timestamp, const Quaternion<float>& quat) {
	// Calculate Euler angles (roll, pitch, and yaw) from the unit quaternion.
	float roll = RAD_TO_ANGLE * atan2(2.0f * (quat.w() * quat.x() + quat.y() * quat.z()),
			1.0f - 2.0f * (quat.x() * quat.x() + quat.y() * quat.y()));
	float pitch = RAD_TO_ANGLE * asin(max(-1.0f, min(1.0f, 2.0f * (quat.w() * quat.y() - quat.z() * quat.x()))));
	float yaw = RAD_TO_ANGLE * atan2(2.0f * (quat.w() * quat.z() + quat.x() * quat.y()),
			1.0f - 2.0f * (quat.y() * quat.y() + quat.z() * quat.z()));

	// Convert the floating point angles in radians to a scale from 0 to 18.
	//roll = static_cast<int>((roll + (float)M_PI)/(M_PI * 2.0f) * 24 + 50);
	//pitch = static_cast<int>((pitch + (float)M_PI/2.0f)/M_PI * 127);
	//yaw = static_cast<int>((yaw + (float)M_PI)/(M_PI * 2.0f) * 24 + 50);

	//give data to person
	myomap[myo]->setData(roll, pitch, yaw);
}

/*
   void DataCollector::onPose(Myo* myo, uint64_t timestamp, Pose pose)
   {
   currentPose = pose;
   if (pose != Pose::unknown && pose != Pose::rest) {
// Tell the Myo to stay unlocked until told otherwise. We do that here so you can hold the poses without the
// Myo becoming locked.
myo->unlock(Myo::unlockHold);
// Notify the Myo that the pose has resulted in an action, in this case changing
// the text on the screen. The Myo will vibrate.
myo->notifyUserAction();
} else {
// Tell the Myo to stay unlocked only for a short period. This allows the Myo to stay unlocked while poses
// are being performed, but lock after inactivity.
myo->unlock(Myo::unlockTimed);
}
}
*/

//XXX REALLY DONT CARE :^)
// onArmSync() is called whenever Myo has recognized a Sync Gesture after someone has put it on their
// arm. This lets Myo know which arm it's on and which way it's facing.
/*
   void DataCollector::onArmSync(Myo* myo, uint64_t timestamp, Arm arm, XDirection xDirection)
   {
   onArm = true;
   whichArm = arm;
   }
// onArmUnsync() is called whenever Myo has detected that it was moved from a stable position on a person's arm after
// it recognized the arm. Typically this happens when someone takes Myo off of their arm, but it can also happen
// when Myo is moved around on the arm.
void DataCollector::onArmUnsync(Myo* myo, uint64_t timestamp)
{
onArm = false;
}
// onUnlock() is called whenever Myo has become unlocked, and will start delivering pose events.
void DataCollector::onUnlock(Myo* myo, uint64_t timestamp)
{
isUnlocked = true;
}
// onLock() is called whenever Myo has become locked. No pose events will be sent until the Myo is unlocked again.
void DataCollector::onLock(Myo* myo, uint64_t timestamp)
{
isUnlocked = false;
}
*/
