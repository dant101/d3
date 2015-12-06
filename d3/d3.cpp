// d3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <winsock2.h>
#include <system_error>

#pragma comment(lib, "Ws2_32.lib")

#define PORT 7104

int main()
{

	WSADATA wsa;
	SOCKET s;
	struct sockaddr_in local_addr;

	// Set up winsock
	printf("Initialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Initialised.\n");

	
	// Create a socket on local host
	s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (s == INVALID_SOCKET) {
		printf("Cannot create socket. Error code: %d\n", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Socket created.\n");
	

	// Set up port
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(PORT);
	local_addr.sin_addr.s_addr = INADDR_ANY;
	

	// Bind port to socket
	if (bind(s, (struct sockaddr *) &local_addr, sizeof(local_addr)) == SOCKET_ERROR) {
		printf("Bind Failed. Error code: %d\n", WSAGetLastError());
		exit(EXIT_FAILURE);
	}


	// Wait to receive a message 
	char buffer[100];
	recv(s,buffer, 100, 0);


	// Print message
	printf(buffer);
	printf("\n");
	

	// Cleanup
	closesocket(s);
	WSACleanup();

    return 0;
}

