#include <string>
#include <iostream>
#include <chrono>

#ifndef MACHINE
#define MACHINE

#define TIMEOUT 2.5
#define FPS_NO 10

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
	void update();

	std::string machine_id;
	Status status;

private:
	std::string version;
	int fps[FPS_NO];
	int fps_count;
	int fps_last;
	std::chrono::time_point<std::chrono::system_clock> last_access;


};

#endif