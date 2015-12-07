#include "stdafx.h"
#include "machine.h"


Machine::Machine(std::string machine_id_) : machine_id(machine_id_)
{
	status = Status::NOT_CONNECTED;
}


Machine::~Machine()
{
}

void Machine::printMachine() {
	switch (status)
	{
	case Status::NOT_CONNECTED:
			std::cout << "| Machine ID: " << machine_id << " | Status: Not connected |\n";
			break;

	default:
		break;
	}
}
