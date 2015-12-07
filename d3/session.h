#include <string>
#include <vector>
#include "machine.h"
#include <iostream>

#ifndef SESSION
#define SESSION

class Session
{
public:
	
	Session(std::string session_name, std::string creator, std::vector<std::string> machine_ids);
	virtual ~Session();

	void printSession();

	std::string session_name;
	std::string creator;
	std::vector<Machine> machines;
};

#endif