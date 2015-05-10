/*
 * ControlEntity.cpp
 *
 *  Created on: 3 May 2015
 *      Author: Jan Kumor
 */

#include <iostream>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>

#include <cstring>

#include <memory>

#include "ControlEntity.hpp"
#include "../../proto/include/comuactiv/ComuactivServerSlot.hpp"

using namespace comuactiv::ce_app;
using namespace comuactiv::proto;

namespace comuactiv {
namespace ce_app {

ControlEntity::ControlEntity() {

}

ControlEntity& ControlEntity::ControlEntity::getInstance() {
	static ControlEntity instance;
	return instance;
}

void ControlEntity::start() {
	std::cout << "CE Started" << std::endl;

	int sock;
	unsigned int length;
	struct sockaddr_in server;
	int msgsock;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		perror("opening stream socket");
		exit(1);
	}
	/* dowiaz adres do gniazda */
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(CE_PORT);
	if (bind(sock, (struct sockaddr *) &server, sizeof server) == -1) {
		perror("binding stream socket");
		exit(1);
	}
	/* wydrukuj na konsoli przydzielony port */
	length = sizeof(server);
	if (getsockname(sock, (struct sockaddr*) &server, &length) == -1) {
		perror("getting socket name");
		exit(1);
	}
	std::cout << "CE is listening for incoming connections on port: " << ntohs(server.sin_port) << std::endl;

	listen(sock, 5);
	std::cout << "Sock: " << sock << std::endl;
	do {
		msgsock = accept(sock,(struct sockaddr*) 0,(unsigned int*) 0);
		if (msgsock == -1 ) {
			perror("accept");
		} else {
			std::cout << "CE: Incoming connection accepted on socket: " << msgsock << std::endl;
			std::unique_ptr<ComuactivServerSlot> slot(new ComuactivServerSlot(msgsock));
			slot->run();
		}

	} while(1);
}

} /* namespace ce_app */
} /* namespace comuactiv */
