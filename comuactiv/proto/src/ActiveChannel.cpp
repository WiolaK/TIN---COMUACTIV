/*
 * ActiveChannel.cpp
 *
 *  Created on: 4 May 2015
 *      Author: Jan Kumor
 */

#include "ActiveChannel.hpp"

#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include "comuactiv_utils.hpp"
#include "messages/RawMessage.hpp"

using namespace comuactiv::proto;

#define LOG(x) std::cout << "ActiveChannel #" << id_ << ": " << x << std::endl

namespace comuactiv {
namespace proto {

int ActiveChannel::counter_ = 0;

ActiveChannel::ActiveChannel(std::string host, std::string port)
: host_(host),
  port_(port) {
	id_ = ++counter_;
	LOG("created.");
	initialize();
}

ActiveChannel::~ActiveChannel() {
	close(sock_);
	LOG("closed.");
}

void* ActiveChannel::run() {
	return nullptr;
}

void ActiveChannel::initialize() {
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

void ActiveChannel::writeMessage(messages::pRawMessage msg) {
	LOG("writing: " << std::string(msg->array, msg->length));

	//writig in loop to be sure that all data is sent
	for( int remaining = msg->length; remaining > 0; ) {
		int sent = write( sock_, msg->array, msg->length );
		if ( sent == -1 ) {
			perror("writing on stream socket");
		}
		remaining-=sent;
	}
}

void ActiveChannel::listenResponse() {
	LOG("listening for response...");
	char buf[1024];
	int rval;

	do {
		if ((rval = read(sock_,buf, 1024)) == -1) {
			perror("reading stream message");
		}
		if (rval == 0) {
			LOG("ending connection.");
		} else {
			LOG("-->" << buf);
		}
	} while (rval != 0);;
}

} /* namespace proto */
} /* namespace comuactiv */
