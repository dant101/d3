#include "udpSocket.h"
#include "parser.h"
#include "session.h"
#include <string>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>

#pragma comment(lib, "Ws2_32.lib")

#define PROTOCOL1 7106
#define PROTOCOL2 7104
#define TIME_UPDATE 5
#define MAX_MESSAGE_LENGTH 128

#ifndef d3
#define d3

enum class MessageType {SESSION_STARTUP, MACHINE_STARTUP, MACHINESTATUS, MESSAGE_ERROR};

WSADATA wsa;
std::vector<Session> *sessions;
std::mutex sessionLock;

int main();

void winsockSetUp();
void consoleUpdate();
void listenUDP(UDPSocket s);
MessageType enumHash(std::string str);

void sessionStartup(std::vector<std::string> *v);
void insertSession(Session *s);
void machineStartup(std::vector<std::string> *v);
void machineStatus(std::vector<std::string> *v);

#endif
