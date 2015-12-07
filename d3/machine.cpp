#include "stdafx.h"
#include "machine.h"

void Machine::init() {
	fps_count = 0;
	fps_last = 0;
	last_access = std::chrono::system_clock::now();
}

Machine::Machine(std::string machine_id_) : machine_id(machine_id_)
{
	status = Status::NOT_CONNECTED;
	init();
}

Machine::Machine(std::string machine_id_, Status status_) : machine_id(machine_id_), status(status_) {
	init();
}



Machine::~Machine()
{
}

void Machine::printMachine() {
	update();

	switch (status)
	{
	case Status::NOT_CONNECTED:
			std::cout << "| Machine ID: " << machine_id << " | Status: Not connected |\n";
			break;
	case Status::CONNECTED:
			std::cout << "| Machine ID: " << machine_id << " | Status: Connected |\n";
			break;
	case Status::ACTIVE:
		std::cout << "| Machine ID: " << machine_id << " | Status: Active | Version: " << version << " | Average FPS: " << averageFPS() << " |\n";
		break;
	case Status::LOST:
		std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - last_access;
		std::cout << "| Machine ID: " << machine_id << " | Status: LOST | Version: " << version << " | Last Transmission: ";
		std::cout << elapsed_seconds.count() << "s |\n";
		break;
	default:
		break;
	}
}

// Update a machines info with the latest heartbeat
void Machine::heartBeat(std::string version_, std::string fps_) {
	status = Status::ACTIVE;
	version = version_;
	last_access = std::chrono::system_clock::now();
	
	int current_fps = atoi(fps_.c_str());

	if (fps_count < FPS_NO) {
		fps[fps_count] = current_fps;
		fps_count++;
	} else {
		fps[fps_last] = current_fps;
		fps_last++;
		fps_last %= FPS_NO;
	}

}

// Return average fps of the last FPS_NO heartbeats
int Machine::averageFPS() {
	if (fps_count == 0) return 0;

	int total = 0;
	for (int i = 0; i < fps_count; i++) {
		total += fps[i];
	}
	double avg = total / (double)fps_count;
	return (int) avg;
}

void Machine::update() {

	// Get time since last update
	std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - last_access;
	std::cout << elapsed_seconds.count() << "s\n";
	if (status == Status::ACTIVE && elapsed_seconds.count() > TIMEOUT) {
		status = Status::LOST;
		fps_count = 0;
		fps_last = 0;
	}
}
