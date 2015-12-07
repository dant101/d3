#include <string>
#include <iostream>

#ifndef MACHINE
#define MACHINE

enum class Status {ACTIVE, CONNECTED, LOST, NOT_CONNECTED};

class Machine
{
public:
	Machine(std::string machine_id_);
	Machine(std::string machine_id_, Status status_) : machine_id(machine_id_), status(status_) {};
	~Machine();

	void printMachine();

	std::string machine_id;
	Status status;

};

#endif