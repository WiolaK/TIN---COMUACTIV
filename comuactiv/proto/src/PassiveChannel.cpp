/*
 * PassiveChannel.cpp
 *
 *  Created on: 4 May 2015
 *      Author: Jan Kumor
 */

#include "PassiveChannel.hpp"

#include <netinet/in.h>
#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "ActiveChannel.hpp"

#define LOG(x) std::cout << "PassiveChannel #" << id_ << ": " << x << std::endl

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

PassiveChannel::PassiveChannel(pAChannel active)
: sock_(active->getSock()) {
	id_ = ++counter_;
	pthread_create(&tid, nullptr, &execute, this);
}

PassiveChannel::~PassiveChannel() {
	pthread_join(tid, nullptr);
	LOG("thread joined.");
	close(sock_);
	LOG("closed.");
}

void* PassiveChannel::run() {
	LOG("thread started.");
	if( sock_ == -1) {
		initialize();
	}
	work();
	LOG("work stopped.");
	return nullptr;
}

void PassiveChannel::initialize() {
	unsigned int length;

	SocketAddressIn serverAddress;

	sock_ = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_ == -1) {
		perror("opening stream socket");
		exit(1);
	}
	LOG("initialising on socket: "<< sock_);
	//binding address to socket
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = 0;
	if (bind(sock_, reinterpret_cast<SocketAddress*>(&serverAddress), sizeof serverAddress) == -1) {
		perror("binding stream socket");
		exit(1);
	}

	length = sizeof(serverAddress);
	if (getsockname(sock_, reinterpret_cast<SocketAddress*>(&serverAddress), &length) == -1) {
		perror("getting socket name");
		exit(1);
	}
	//printing assigned port
	LOG("port: " << ntohs(serverAddress.sin_port));

	listen(sock_, 1);
	LOG("is listening really hard ^^");

	sock_ = accept(sock_,(struct sockaddr*) 0,(unsigned int*) 0);
	if (sock_ == -1 ) {
		perror("accept");
	} else {
		LOG("incoming connection accepted on port: " << ntohs(serverAddress.sin_port));
	}
}

void PassiveChannel::work() {
	LOG("work started.");
	char buf[1024];
	int rval;

	/*do {
		if ((rval = read(sock_,buf, 1024)) == -1) {
			perror("reading stream message");
		}
		if (rval == 0) {
			LOG("ending connection.");
		} else {
			LOG("-->" << buf);
		}
	} while (rval != 0);*/
}

} /* namespace proto */
} /* namespace comuactiv */
