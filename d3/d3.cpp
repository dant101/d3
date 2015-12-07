// d3.cpp : Defines the entry point for the console application.

/* 
 * General Workflow of d3
 * 
 * SESSION2 is called creating a session of unconnected machines, sessions with the same name are overridden
 * MACHINE is called which attempts to connect to it's relevant session, machines with the same name are overriden
 * MACHINESTATUS is called which updates all relevant machines in each session with fps and version info
 * 
 * Every TIME_UPDATE, all sessions are printed to console
 * If a machine doesn't communicate for TIMEOUT seconds, assume it's connection has been lost
 *
 */


#include "stdafx.h"
#include "d3.h"



int main() {

	// Set up winsock
	winsockSetUp();

	// Set up sessions
	sessions = new std::vector<Session>();

	// Set up UDP sockets for protocols
	UDPSocket protocol1("Protocol 1", PROTOCOL1);
	UDPSocket protocol2("Protocol 2", PROTOCOL2);

	try {
		// Listen for UDP's and deal with the inputs
		std::thread p1(listenUDP, protocol1);
		std::thread p2(listenUDP, protocol2);

		// Print out sessions every TIME_UPDATE
		std::thread updater(consoleUpdate);

		// Wait for threads to finish listening
		p1.join();
		p2.join();
		updater.join();
	}
	catch (const std::system_error& e) {
		// Thread error
		std::cout << "Caught system_error with code " << e.code()
			<< " meaning " << e.what() << '\n';
	}

	// Cleanup
	WSACleanup();
    return 0;
}

void consoleUpdate() {
	while (true) {

		sessionLock.lock();

		// Loop through sessions
		for (std::vector<Session>::iterator sess_it = sessions->begin(); sess_it < sessions->end(); sess_it++) {
			(*sess_it).printSession();
		}

		sessionLock.unlock();

		// Sleep current thread
		std::this_thread::sleep_for(std::chrono::seconds(TIME_UPDATE));
	}
}

void listenUDP(UDPSocket s) {
	while (true) {

		// Read message
		char buffer[MAX_MESSAGE_LENGTH];
		memset(buffer, 0, sizeof(buffer));
		s.recieveData(buffer, MAX_MESSAGE_LENGTH);

		// Parse message
		std::vector<std::string> *v = new std::vector<std::string>();
		parse(buffer, '|', v, sizeof(buffer));

		// Call relevent methods
		// Lock to ensure mutex when editing the sessions vector
		sessionLock.lock();
		switch (enumHash(*(v->begin()))) {
		case MessageType::SESSION_STARTUP:
			sessionStartup(v);
			break;
		case MessageType::MACHINE_STARTUP:
			machineStartup(v);
			break;
		case MessageType::MACHINESTATUS:
			machineStatus(v);
			break;
		default:
			break;
		}
		sessionLock.unlock();
	}
}

void machineStatus(std::vector<std::string> *v) {

	if (v->size() != 4) {
		// Error - somethings missing or there's something extra
		return;
	}

	std::string machine_id = v->at(1);
	std::string version = v->at(2);
	std::string fps = v->at(3);

	// Loop through sessions
	for (std::vector<Session>::iterator sess_it = sessions->begin(); sess_it < sessions->end(); sess_it++) {

		// Loop through that sessions machines
		for (std::vector<Machine>::iterator machine_it = (*sess_it).machines.begin(); machine_it < (*sess_it).machines.end(); machine_it++) {

			// Compare machine names
			if ((*machine_it).machine_id.compare(machine_id) == 0) {

				// If machines connected - heartbeat
				if ((*machine_it).status != Status::NOT_CONNECTED)
					(*machine_it).heartBeat(version, fps);
			}
		}
	}
}

void machineStartup(std::vector<std::string> *v) {

	if (v->size() != 3) {
		// Error - somethings missing or there's something extra
		return;
	}

	std::string machine_id = v->at(1);
	std::string session_name = v->at(2);

	// Loop through sessions
	for (std::vector<Session>::iterator sess_it = sessions->begin(); sess_it < sessions->end(); sess_it++) {

		// Check which sessions the machine matches
		if ((*sess_it).session_name.compare(session_name) == 0) {

			// Loop through that sessions machines
			for (std::vector<Machine>::iterator machine_it = (*sess_it).machines.begin(); machine_it < (*sess_it).machines.end(); machine_it++) {

				// Compare machine names
				if ((*machine_it).machine_id.compare(machine_id) == 0) {
					(*machine_it) = *(new Machine(machine_id, Status::CONNECTED));
				}
			}
		}
	}
}

void sessionStartup(std::vector<std::string> *v) {

	if (v->size() < 3) {
		// Error - Session needs at least a name and creator
		return;
	}

	Session *session = NULL;

	if (v->size() == 3) {
		// Empty session
		session = new Session(*(v->begin() + 1), *(v->begin() + 2), std::vector<std::string>());
	} else {
		// Normal session
		std::vector<std::string> subVector(v->begin() + 3, v->end());
		session = new Session(*(v->begin() + 1), *(v->begin() + 2), subVector);
	}

	insertSession(session);

}

// Insert a new session or replace one that already exist
void insertSession(Session *s) {

	for (std::vector<Session>::iterator it = sessions->begin(); it < sessions->end(); it++) {
		// If names match, replace
		if ((*it).session_name.compare(s->session_name) == 0) {
			(*it) = *s;
			return;
		}
	}

	// Else no matches, so just add a new session
	sessions->push_back(*s);

}

// For switching on a string
MessageType enumHash(std::string str) {
	if (str.compare("SESSION2") == 0) return MessageType::SESSION_STARTUP;
	if (str.compare("MACHINE") == 0) return MessageType::MACHINE_STARTUP;
	if (str.compare("MACHINESTATUS") == 0) return MessageType::MACHINESTATUS;
	return MessageType::MESSAGE_ERROR;
}

void winsockSetUp() {

	// Set up winsock
	std::cout << "Initialising Winsock...\n";
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		std::cout << "Failed. Error Code : " << WSAGetLastError() << "\n";
		exit(EXIT_FAILURE);
	}
	std::cout << "Initialised.\n";
}



