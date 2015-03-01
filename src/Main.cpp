
#include <iostream>
#include <vector>
#include <myo/myo.hpp>
#include "person.hpp"
#include "myo_RPP.cpp"

using namespace std;

int main(int argc, char** argv)
{

	//Create vector of Person
	vector<Person> people;
	//Add 8 people
	for(int i = 0; i < 8; i++)
		people.push_back(Person());

	//Instantiate DataCollector
	DataCollector dc(people);

	try {
		Hub hub("com.example.hello-myo");
		hub.addListener(&dc);
	while (1) {
		hub.run(1000/20);
	}
	// If a standard exception occurred, we print out its message and exit.
	} catch (const exception& e) {
		cerr << "Error: " << e.what() << endl;
		cerr << "Press enter to continue.";
		cin.ignore();
		return 1;
	}

}
