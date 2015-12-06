#include "stdafx.h"
#include "UDPSocket.h"


UDPSocket::UDPSocket(std::string name, u_short port) {

	// Create a socket
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock == INVALID_SOCKET) {
		printf("Cannot create socket. Error code: %d\n", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	std::cout << name << " socket created.\n";


	// Set up socket address and port
	struct sockaddr_in sock_addr;
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_port = htons(port);
	sock_addr.sin_addr.s_addr = INADDR_ANY;


	// Bind port to socket
	if (bind(sock, (struct sockaddr *) &sock_addr, sizeof(sock_addr)) == SOCKET_ERROR) {
		printf("Bind Failed. Error code: %d\n", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

}

UDPSocket::~UDPSocket() {
	closesocket(sock);
}

void UDPSocket::recieveData(char* buffer, int size, int flags) {
	// Wait to receive a message
	recv(sock, buffer, size, flags);
}