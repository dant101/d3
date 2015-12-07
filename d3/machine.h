#include <string>
#include <iostream>

#ifndef MACHINE
#define MACHINE

#define TIMEOUT 3
#define FPS_NO 3

enum class Status {ACTIVE, CONNECTED, LOST, NOT_CONNECTED};

class Machine
{
public:
	Machine(std::string machine_id_);
	Machine(std::string machine_id_, Status status_);
	~Machine();

	void init();
	void printMachine();
	void heartBeat(std::string version, std::string fps);
	int averageFPS();

	std::string machine_id;
	Status status;

private:
	std::string version;
	int fps[FPS_NO];
	int fps_count;
	int fps_last;

};

#endif