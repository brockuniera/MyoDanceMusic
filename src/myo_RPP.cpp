
// Copyright (C) 2013-2014 Thalmic Labs Inc.
// Distributed under the Myo SDK license agreement. See LICENSE.txt for details.
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

// The only file that needs to be included to use the Myo C++ SDK is myo.hpp.
#include <myo/myo.hpp>

#include "person.hpp"

using namespace std;
using namespace myo;

// Classes that inherit from DeviceListener can be used to receive events from Myo devices. DeviceListener
// provides several virtual functions for handling different kinds of events. If you do not override an event, the
// default behavior is to do nothing.
class DataCollector : public DeviceListener {
	private:
		//Map to associate a Myo to a Person
		map<Myo*, Person*> myomap;
		vector<Person> &people;

		bool onArm;
		Arm whichArm;
		// This is set by onUnlocked() and onLocked() above.
		bool isUnlocked;
		// These values are set by onOrientationData() and onPose() above.
		int roll_w, pitch_w, yaw_w;
		Pose currentPose;
		
	public:
		DataCollector(vector<Person> &p)
			: onArm(false), isUnlocked(false), roll_w(0), pitch_w(0), yaw_w(0), currentPose(), people(p)
		 	{/*nothing*/}

		void onPair(Myo* myo, uint64_t timestamp, FirmwareVersion firmwareVersion)
		{
			cout << "A Myo connected!" << endl;
			myomap[myo] = &(people[0]);
		}

		void onUnpair(Myo* myo, uint64_t timestamp)
		{
			// We've lost a Myo.
			// Let's clean up some leftover state.
			roll_w = 0;
			pitch_w = 0;
			yaw_w = 0;
			onArm = false;
			isUnlocked = false;
		}
		// onOrientationData() is called whenever the Myo device provides its current orientation, which is represented
		// as a unit quaternion.
		void onOrientationData(Myo* myo, uint64_t timestamp, const Quaternion<float>& quat)
		{
			using std::atan2;
			using std::asin;
			using std::sqrt;
			using std::max;
			using std::min;
			// Calculate Euler angles (roll, pitch, and yaw) from the unit quaternion.
			float roll = atan2(2.0f * (quat.w() * quat.x() + quat.y() * quat.z()),
							   1.0f - 2.0f * (quat.x() * quat.x() + quat.y() * quat.y()));
			float pitch = asin(max(-1.0f, min(1.0f, 2.0f * (quat.w() * quat.y() - quat.z() * quat.x()))));
			float yaw = atan2(2.0f * (quat.w() * quat.z() + quat.x() * quat.y()),
							1.0f - 2.0f * (quat.y() * quat.y() + quat.z() * quat.z()));
			// Convert the floating point angles in radians to a scale from 0 to 18.
		  //  roll_w = static_cast<int>((roll + (float)M_PI)/(M_PI * 2.0f) * 18);
		  //  pitch_w = static_cast<int>((pitch + (float)M_PI/2.0f)/M_PI * 18);
		  //  yaw_w = static_cast<int>((yaw + (float)M_PI)/(M_PI * 2.0f) * 18);

		}
		// onPose() is called whenever the Myo detects that the person wearing it has changed their pose, for example,
		// making a fist, or not making a fist anymore.
		void onPose(Myo* myo, uint64_t timestamp, Pose pose)
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
		// onArmSync() is called whenever Myo has recognized a Sync Gesture after someone has put it on their
		// arm. This lets Myo know which arm it's on and which way it's facing.
		void onArmSync(Myo* myo, uint64_t timestamp, Arm arm, XDirection xDirection)
		{
			onArm = true;
			whichArm = arm;
		}
		// onArmUnsync() is called whenever Myo has detected that it was moved from a stable position on a person's arm after
		// it recognized the arm. Typically this happens when someone takes Myo off of their arm, but it can also happen
		// when Myo is moved around on the arm.
		void onArmUnsync(Myo* myo, uint64_t timestamp)
		{
			onArm = false;
		}
		// onUnlock() is called whenever Myo has become unlocked, and will start delivering pose events.
		void onUnlock(Myo* myo, uint64_t timestamp)
		{
			isUnlocked = true;
		}
		// onLock() is called whenever Myo has become locked. No pose events will be sent until the Myo is unlocked again.
		void onLock(Myo* myo, uint64_t timestamp)
		{
			isUnlocked = false;
		}
		// There are other virtual functions in DeviceListener that we could override here, like onAccelerometerData().
		// For this example, the functions overridden above are sufficient.
		// We define this function to print the current values that were updated by the on...() functions above.
		void print()
		{
		}
};
