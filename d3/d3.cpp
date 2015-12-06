// d3.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "UDPSocket.h"

#pragma comment(lib, "Ws2_32.lib")

#define PROTOCOL1 7106
#define PROTOCOL2 7104

int main() {

	// Set up winsock
	WSADATA wsa;
	printf("Initialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Initialised.\n");


	UDPSocket protocol1("Protocol 1", PROTOCOL1);
	UDPSocket protocol2("Protocol 2", PROTOCOL2);
	char buffer[100];
	protocol1.recieveData(buffer, 20);
	printf(buffer);
	printf("\n");
	protocol2.recieveData(buffer, 20);
	printf(buffer);
	printf("\n");

	// Cleanup
	WSACleanup();
    return 0;
}



