// d3.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "d3.h"



int main() {

	char buffer[100] = "paulspc|peterspc             |davespc      ";

	std::vector<std::string> v;
	parse(buffer, '|', &v, sizeof(buffer));


	std::string s1 = "my session";
	std::string s2 = "paulspc";
	Session s(s1, s2, v);

	s.printSession();



	// Set up winsock
	winsockSetUp();

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
		std::vector<std::string> v;
		parse(buffer, '|', &v, sizeof(buffer));

		for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); it++) {
			std::cout << *it << "\n";
		}

		std::cout << buffer << "\n";

	}
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



