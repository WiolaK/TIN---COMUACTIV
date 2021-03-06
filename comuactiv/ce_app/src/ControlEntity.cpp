/*
 * ControlEntity.cpp
 *
 *  Created on: 3 May 2015
 *      Author: Jan Kumor
 */
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <pthread.h>
#include <mutex>

#include "../../proto/include/comuactiv/SendFlowTableCommand.hpp"

#include "ControlEntity.hpp"

#include "../../proto/include/comuactiv/FlowTable.hpp"
#include "UserInterface.hpp"

using namespace comuactiv::ce_app;
using namespace comuactiv::proto;
using namespace comuactiv::proto::flowtable;

namespace comuactiv {
namespace ce_app {

ControlEntity::ControlEntity() {
	//Do nothing
}

ControlEntity& ControlEntity::ControlEntity::getInstance() {
	static ControlEntity instance;
	return instance;
}

void ControlEntity::start(std::string port) {
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
	server.sin_port = htons(atoi(port.c_str()));
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

	flowtable_.loadTable("../flowtable.xml");
	flowtable_.checkTable();

	std::mutex slotsMtx;
	std::vector<proto::pComuactivServerSlot> slots;
	UserInterface uI(slots, slotsMtx, flowtable_);

	listen(sock, 5);
	do {
		struct sockaddr connectionAddres;
		unsigned int addrLen = sizeof(struct sockaddr);
		msgsock = accept(sock, &connectionAddres, &addrLen);
		if (msgsock == -1 ) {
			perror("accept");
		} else {
			std::string host(inet_ntoa( reinterpret_cast<struct sockaddr_in*>(&connectionAddres)->sin_addr ) );
			std::cout << "CE: Incoming connection from: " << host << " accepted on socket: " << msgsock << std::endl;
			std::lock_guard<std::mutex> lock(slotsMtx);
			slots.push_back( pComuactivServerSlot(new ComuactivServerSlot(msgsock, host)));
		}
	} while(true);
}

} /* namespace ce_app */
} /* namespace comuactiv */
