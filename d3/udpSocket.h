#include <winsock2.h>
#include <string>
#include <iostream>

#ifndef UDPSOCK
#define UDPSOCK


class UDPSocket {

private:
	SOCKET sock;

public:
	UDPSocket(std::string name, u_short port);
	virtual ~UDPSocket();

	void recieveData(char* buffer, int size, int flags = 0);
};

#endif 