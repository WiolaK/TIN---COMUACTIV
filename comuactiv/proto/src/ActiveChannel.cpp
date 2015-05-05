/*
 * ActiveChannel.cpp
 *
 *  Created on: 4 May 2015
 *      Author: Jan Kumor
 */

#include "ActiveChannel.hpp"

#include <cstring>
#include <stdio.h>
#include <iostream>

#include "comuactiv_utils.hpp"

using namespace comuactiv::proto;

namespace comuactiv {
namespace proto {

#define DATA "Half a league, half a league . . ."

int ActiveChannel::counter_ = 0;

ActiveChannel::ActiveChannel(std::string host, std::string port)
: host_(host),
  port_(port) {
	id_ = ++counter_;
	//pthread_create(&tid, nullptr, &execute, this);
	initialize();
}

ActiveChannel::~ActiveChannel() {
	close(sock_);
	std::cout << "Closing PassiveChannel #" << id_ << std::endl;
}

void* ActiveChannel::run() {
	return nullptr;
}

void ActiveChannel::initialize() {
	std::cout << "Creating ActiveChannel #" << counter_ << " on socket: "<< sock_ << std::endl;
	SocketAddressIn serverAddress;
	HostEntry* hostEntry;

	//Creating socket
	sock_ =	socket(AF_INET, SOCK_STREAM, 0);
	if (sock_ == -1) {
		perror("opening stream socket");
		exit(1);
	}
	//Resolving address
	serverAddress.sin_family = AF_INET;
	hostEntry = gethostbyname(host_.c_str());
	if (hostEntry == nullptr) {
		std::cerr << host_ << " : unknown host" << std::endl;
		exit(2);
	}
	memcpy( (char*) &serverAddress.sin_addr, (char*)hostEntry->h_addr, hostEntry->h_length);
	serverAddress.sin_port	= htons(atoi(port_.c_str()));
	if ( connect(sock_, (SocketAddress*) &serverAddress, sizeof serverAddress) == -1) {
		perror("connecting stream socket");
		exit(1);
	}
}

void ActiveChannel::writeData(char* data) {
	do {
		if (write( sock_, data, sizeof data ) == -1) {
			perror("writing on stream socket");
		}
		sleep(5);
	}while(true);
}

} /* namespace proto */
} /* namespace comuactiv */
