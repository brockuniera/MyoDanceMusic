
#include <iostream>
#include <vector>

//timers
#include <mach/clock.h>
#include <mach/mach.h>

#include <unistd.h> //usleep

#include <myo/myo.hpp>

#include "MyoConnector.hpp"
#include "Person.hpp" 
#include "MidiPlayer.hpp"


#define SECOND_TO_MICRO	1000000 //one million
#define NANO_TO_MICRO	(1.0/1000.0) //one over 1000

using std::cout;
using std::cerr;
using std::endl;

int main(int argc, char** argv)
{
	//Create vector of Person
	vector<Person> people;
	//Add 8 people
	//TODO individualize perosons
	for(int i = 0; i < 8; i++)
		people.push_back(Person(i));

	//Instantiate DataCollector
	DataCollector dc(people.begin(), people.end());


	//setup clocks
	clock_serv_t cclock;
	host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);

	try {
		Hub hub("com.ayy.lmao");
		hub.addListener(&dc);

		while (1) {
			struct timespec start, end;
			mach_timespec_t mts;

			//start timer...
			clock_get_time(cclock, &mts);
			start.tv_sec = mts.tv_sec;
			start.tv_nsec = mts.tv_nsec;

			//update myo a lot
			hub.run(1000/20);

			//...stop
			clock_get_time(cclock, &mts);
			end.tv_sec = mts.tv_sec;
			end.tv_nsec = mts.tv_nsec;

			unsigned int microDiff = difftime(end.tv_sec, start.tv_sec);
			//convert to microseconds
			microDiff *= SECOND_TO_MICRO; 
			//add nanoseconds difference (final - initial), converted to microseconds
			microDiff += (end.tv_nsec - start.tv_nsec) * NANO_TO_MICRO;

			//TODO allow changes in bpm :^)
			//Play notes needs to happen every 16th note
			unsigned int sixteenths = 125000;
			usleep(sixteenths - microDiff);

			//let MidiPlayer stop notes
			MidiPlayer::getInstance().stopNotes();

			//play notes
			for(Person p : people){
				if(p.hasStarted){
					p.playNotes();
				}
			}
		}

		// If a standard exception occurred, we print out its message and exit.
	} catch (const exception& e) {
		cerr << "Error: " << e.what() << endl;
		cerr << "Press enter to continue.";
		cin.ignore();
		return 1;
	}

	//free clock
	mach_port_deallocate(mach_task_self(), cclock);

}


