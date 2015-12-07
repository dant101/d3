#include <string>
#include <iostream>

#ifndef MACHINE
#define MACHINE

enum class Status {ACTIVE, CONNECTED, LOST, NOT_CONNECTED};

class Machine
{
public:
	Machine(std::string machine_id_);
	~Machine();

	void printMachine();
private:
	std::string machine_id;
	Status status;

};

#endif