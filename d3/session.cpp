#include "stdafx.h"
#include "session.h"


Session::Session(std::string session_name_, std::string creator_, std::vector<std::string> machine_ids) : session_name(session_name_), creator(creator_)
{

	for (std::vector<std::string>::iterator it = machine_ids.begin(); it != machine_ids.end(); it++) {
		machines.push_back(Machine(*it));
	}

}

void Session::printSession() {
	std::cout << "\n\n";
	std::cout << "| Session: " << session_name << " | Creator: " << creator + " |\n";

	for (std::vector<Machine>::iterator it = machines.begin(); it != machines.end(); it++) {
		(*it).printMachine();
	}

	std::cout << "\n\n";
}


Session::~Session()
{
}


