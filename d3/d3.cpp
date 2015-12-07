// d3.cpp : Defines the entry point for the console application.

/* 
 * General Workflow of d3
 * 
 * SESSION2 is called creating a session of unconnected machines
 * MACHINE is called which attempts to connect to a session
 * MACHINESTATUS is called which updates the machine in each of it's sessions it's connected to
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

	// Listen for UDP's and deal with the inputs
	std::thread p1 (listenUDP, protocol1);
	std::thread p2 (listenUDP, protocol2);

	// Wait for threads to finish listening
	p1.join();
	p2.join();

	// Cleanup
	WSACleanup();
    return 0;
}

void listenUDP(UDPSocket s) {
	while (true) {

		// Read message
		char buffer[100];
		memset(buffer, 0, sizeof(buffer));
		s.recieveData(buffer, 100);

		// Parse message
		std::vector<std::string> *v = new std::vector<std::string>();
		parse(buffer, '|', v, sizeof(buffer));

		// Call relevent methods
		switch (enumHash(*(v->begin()))) {
		case MessageType::SESSION_STARTUP:
			sessionStartup(v);
			break;
		case MessageType::MACHINE_STARTUP:
			machineStartup(v);
			break;
		case MessageType::MACHINESTATUS:
			
			break;
		default:
			break;
		}
	}
}

void machineStartup(std::vector<std::string> *v) {
	sessionLock.lock();

	if (v->size() != 3) {
		// Error - somethings missing or there's something extra
		return;
	}

	// Loop through sessions
	for (std::vector<Session>::iterator sess_it = sessions->begin(); sess_it < sessions->end(); sess_it++) {

		// Check which sessions the machine matches
		if ((*sess_it).session_name.compare(v->at(2)) == 0) {

			// Loop through that sessions machines
			for (std::vector<Machine>::iterator machine_it = (*sess_it).machines.begin(); machine_it < (*sess_it).machines.end(); machine_it++) {

				// Compare machine names
				if ((*machine_it).machine_id.compare(v->at(1)) == 0) {
					(*machine_it) = *(new Machine(v->at(1), Status::CONNECTED));
				}
			}
		}
	}

	std::cout << "Machine startup " << v->at(1) << v->at(2) << "\n";
	for (std::vector<Session>::iterator it = sessions->begin(); it < sessions->end(); it++) {
		(*it).printSession();
	}

	sessionLock.unlock();
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

	std::cout << "Session startup " << v->at(1) << v->at(2) << "\n";
	for (std::vector<Session>::iterator it = sessions->begin(); it < sessions->end(); it++) {
		(*it).printSession();
	}
}

// Insert a new session or replace one that already exist
void insertSession(Session *s) {
	sessionLock.lock();

	for (std::vector<Session>::iterator it = sessions->begin(); it < sessions->end(); it++) {
		// If names match, replace
		if ((*it).session_name.compare(s->session_name) == 0) {
			(*it) = *s;
			sessionLock.unlock();
			return;
		}
	}

	// Else no matches, so just add a new session
	sessions->push_back(*s);
	sessionLock.unlock();
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



