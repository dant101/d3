#include "udpSocket.h"
#include "parser.h"
#include <string>
#include <thread>
#include <vector>

#pragma comment(lib, "Ws2_32.lib")

#define PROTOCOL1 7106
#define PROTOCOL2 7104

#ifndef d3
#define d3

WSADATA wsa;

int main();
void winsockSetUp();
void listenUDP(UDPSocket s);

#endif
