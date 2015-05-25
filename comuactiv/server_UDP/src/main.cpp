/*
 * main.cpp
 *
 *  Created on: May 25, 2015
 *      Author: Wiola Klimczak
 */

#include "ServerUDP.hpp"

using namespace std;

using namespace comuactiv::server_udp;

int main(int argc, char* argv[])
{
	// ServerUDP* server = new ServerUDP;

	ServerUDP* server;
	server = ServerUDP::getInstance();

	int socket, port;

	socket = server->get_socket();

	port = server->get_port();

	cout << socket;
	cout << port;


	return 0;
}




