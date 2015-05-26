/*
 * RealChannelActive.cpp
 *
 *  Created on: 4 May 2015
 *      Author: Jan Kumor
 */

#include "RealChannelActive.hpp"

#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "../messages/MessageFactory.hpp"
#include "../utils/exceptions.hpp"
#include "../utils/types.hpp"

using namespace comuactiv::proto;
using namespace comuactiv::proto::messages;
using namespace comuactiv::proto::utils;

#define LOG(x) std::cout << "RealChannelActive#" << id_ << ": " << x << std::endl

namespace comuactiv {
namespace proto {
namespace channels {

RealChannelActive::RealChannelActive()
: id_(0) {
}

RealChannelActive::RealChannelActive(int sock)
: id_(0),
  sock_(sock) {

}

RealChannelActive::~RealChannelActive() {
	close(sock_);
	LOG("Closed.");
}

bool RealChannelActive::start() {
	LOG("ACTIVE START");
	initializeActive();
}

void RealChannelActive::initializeActive() {
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
	//hostEntry = gethostbyname(host_.c_str());
	const char host_[] = "127.0.0.1";
	hostEntry = gethostbyname(host_);
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

void RealChannelActive::writeMessage(pRawMessage msg) {
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

pMessage RealChannelActive::readMessage() {
	pMessage msg(new Message());
	msg->setHeader(readHeader());
	msg->setData( readData( msg->getHeader().length_-sizeof(Message::MessageHeader) ) );
	return msg;
}

Message::MessageHeader RealChannelActive::readHeader() {
	//creating buffer
	int bufferSize = sizeof(Message::MessageHeader);
	char* buffer = new char[bufferSize];
	for(int i=0; i<bufferSize; i++)
		buffer[i] = 0;
	int rval;

	for( int bytesToRead = bufferSize; bytesToRead > 0 && rval != 0; bytesToRead-=rval) {
		rval = read(sock_, buffer+(bufferSize-bytesToRead), bytesToRead);
		if( rval == -1 ) {
			perror("reading stream message");
		} else if ( rval == 0) {
			LOG("ending connection.");
			throw connectionEndException();
		} else {
			LOG("-->" << std::string(buffer+(bufferSize-bytesToRead), rval));
		}
	}
	Message::MessageHeader hdr;
	memcpy(&hdr, buffer, bufferSize);
	delete [] buffer;
	return hdr;
}

std::string RealChannelActive::readData(int length) {
	//creating buffer
	int bufferSize = length;
	char* buffer = new char[bufferSize];
	for(int i=0; i<bufferSize; i++)
		buffer[i] = 0;
	int rval;

	for( int bytesToRead = bufferSize; bytesToRead > 0 && rval != 0; bytesToRead-=rval) {
		LOG("Bytes to read: " << bytesToRead);
		rval = read(sock_, buffer+(bufferSize-bytesToRead), bytesToRead);
		if( rval == -1 ) {
			perror("reading stream message");
		} else if ( rval == 0) {
			LOG("ending connection.");
			throw connectionEndException();
		} else {
			LOG("-->" << std::string(buffer+(bufferSize-bytesToRead), rval));
		}
	}

	auto str = std::string(buffer, bufferSize);
	delete [] buffer;
	return str;
}

} /* namespace channels */
} /* namespace proto */
} /* namespace comuactiv */
