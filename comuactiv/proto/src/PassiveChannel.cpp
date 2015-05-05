/*
 * PassiveChannel.cpp
 *
 *  Created on: 4 May 2015
 *      Author: Jan Kumor
 */

#include "PassiveChannel.hpp"

#include <stdio.h>
#include <iostream>

#include "comuactiv_utils.hpp"

using namespace comuactiv::proto;

namespace comuactiv {
namespace proto {

int PassiveChannel::counter_ = 0;

PassiveChannel::PassiveChannel() {
	id_ = ++counter_;
	sock_ = -1;
	pthread_create(&tid, nullptr, &execute, this);
}

PassiveChannel::PassiveChannel(int sock)
: sock_(sock) {
	id_ = ++counter_;
	pthread_create(&tid, nullptr, &execute, this);
}

PassiveChannel::~PassiveChannel() {
	std::cout << "Closing PassiveChannel #" << id_ << std::endl;
	close(sock_);
	pthread_join(tid, nullptr);
}

void* PassiveChannel::run() {
	if( sock_ == -1) {
		initialize();
	}
	work();
	return nullptr;
}

void PassiveChannel::initialize() {
	unsigned int length;
	struct sockaddr_in server;

	sock_ = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_ == -1) {
		perror("opening stream socket");
		exit(1);
	}
	std::cout << "Starting thread. PassiveChannel #" << id_ << " on socket: "<< sock_ << std::endl;
	//binding address to socket
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = 0;
	if (bind(sock_, (struct sockaddr *) &server, sizeof server) == -1) {
		perror("binding stream socket");
		exit(1);
	}

	//printing assigned port
	length = sizeof(server);
	if (getsockname(sock_, (struct sockaddr*) &server, &length) == -1) {
		perror("getting socket name");
		exit(1);
	}
	printf("Socket port #%d\n", ntohs(server.sin_port));

	listen(sock_, 1);

	do {
		std::cout << "PassiveChannel #" << id_ << " is listening really hard ^^" << std::endl;

		sock_ = accept(sock_,(struct sockaddr*) 0,(unsigned int*) 0);
		if (sock_ == -1 ) {
			perror("accept");
		} else {
			work();
		}
		sleep(5);
	} while(true);
}

void PassiveChannel::work() {
	char buf[1024];
	int rval;

	while(true) {
		do {
			if ((rval = read(sock_,buf, 1024)) == -1)
				perror("reading stream message");
			if (rval == 0)
				printf("Ending connection\n");
			else
				printf("-->%s\n", buf);
		} while (rval != 0);
	}
}

} /* namespace proto */
} /* namespace comuactiv */
