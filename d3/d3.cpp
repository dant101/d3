// d3.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "d3.h"

void listenUDP(UDPSocket s) {
	while (true) {
		char buffer[100];
		memset(buffer, 0, sizeof(buffer));

		s.recieveData(buffer, 100);
		std::cout << buffer << "\n";
		
	}
}

int main() {

	winsockSetUp();

	UDPSocket protocol1("Protocol 1", PROTOCOL1);
	UDPSocket protocol2("Protocol 2", PROTOCOL2);

	std::thread p1 (listenUDP, protocol1);
	std::thread p2 (listenUDP, protocol2);

	p1.join();
	p2.join();

	// Cleanup
	WSACleanup();
    return 0;
}

void winsockSetUp() {
	// Set up winsock
	WSADATA wsa;
	printf("Initialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Initialised.\n");
}



