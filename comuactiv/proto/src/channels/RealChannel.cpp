/*
 * RealChannel.cpp
 *
 *  Created on: 4 May 2015
 *      Author: Jan Kumor
 */

#include "RealChannel.hpp"

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

namespace comuactiv {
namespace proto {
namespace channels {

RealChannel::~RealChannel() {
	pthread_join(tid, nullptr);
	log_("Thread joined.");
	close(sock_);
	log_("Closed.");
}

bool RealChannel::start() {
	switch(mode_) {
	case PASSIVE:
		log_("Starting in PASSIVE mode.");
		if(pthread_create(&tid, nullptr, &execute, this)) {
			log_(std::string("Pthread_create failure errno=").append(std::to_string(errno)));
			return false;
		}
		break;

	case ACTIVE:
		log_("Starting in ACTIVE mode.");
		initializeActive();
		break;

	}
	return true;

}

void* RealChannel::run() {
	log_("Running.");
	if( sock_ == -1) {
		initializePassive();
	}
	workPassive();
	return nullptr;
}

void RealChannel::initializeActive() {
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

void RealChannel::initializePassive() {
	unsigned int length;

	SocketAddressIn serverAddress;

	sock_ = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_ == -1) {
		perror("opening stream socket");
		exit(1);
	}
	log_(std::string("On socket: ").append(std::to_string(sock_)));
	//binding address to socket
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;

	serverAddress.sin_port = htons(atoi(port_.c_str()));
	if (bind(sock_, reinterpret_cast<SocketAddress*>(&serverAddress), sizeof serverAddress) == -1) {
		perror("binding stream socket");
		exit(1);
	}

	length = sizeof(serverAddress);
	if (getsockname(sock_, reinterpret_cast<SocketAddress*>(&serverAddress), &length) == -1) {
		perror("getting socket name");
		exit(1);
	}
	log_(std::string("On port: ").append(std::to_string(ntohs(serverAddress.sin_port))));
	port_ = std::to_string(ntohs(serverAddress.sin_port));

	listen(sock_, 1);
	log_("Listening for connection (really hard ^^).");

	sock_ = accept(sock_,(struct sockaddr*) 0,(unsigned int*) 0);
	if (sock_ == -1 ) {
		perror("accept");
	} else {
		log_(std::string("Connection accepted on port: ").append(port_));
	}
}

void RealChannel::workPassive() {
	log_("Work started.");
	while(true) {
		pMessage msg( new Message() );
		try {
			readAndHandleMessage();
		} catch(const connectionEndException& e) {
			break;
		}
	}
	log_("Work stopped.");
}

void RealChannel::writeMessage(pRawMessage msg) {
	log_(std::string("Writing-->").append(std::string(msg->array, msg->length)));

	//writig in loop to be sure that all data is sent
	for( int remaining = msg->length; remaining > 0; ) {
		int sent = write( sock_, msg->array, msg->length );
		if ( sent == -1 ) {
			perror("writing on stream socket");
		}
		remaining-=sent;
	}
}

void RealChannel::writeAndHandleMessage(messages::pRawMessage msg) {
	writeMessage(msg);
	pMessage response = readMessage();
	handle(MessageFactory::getInstance().create(response->getHeader().code_, response->getRaw()));
}

pMessage RealChannel::readMessage() {
	pMessage msg(new Message());
	msg->setHeader(readHeader());
	msg->setData( readData( msg->getHeader().length_-sizeof(Message::MessageHeader) ) );
	return msg;
}

void RealChannel::readAndHandleMessage() {
	pMessage msg = readMessage();
	handle(MessageFactory::getInstance().create(msg->getHeader().code_, msg->getRaw()));
}

Message::MessageHeader RealChannel::readHeader() {
	//creating buffer
	int bufferSize = sizeof(Message::MessageHeader);
	char* buffer = new char[bufferSize];
	for(int i=0; i<bufferSize; i++)
		buffer[i] = 0;
	int rval;

	for( int bytesToRead = bufferSize; bytesToRead > 0; bytesToRead-=rval) {
		rval = read(sock_, buffer+(bufferSize-bytesToRead), bytesToRead);
		if( rval == -1 ) {
			perror("reading stream message");
			exit(1);
		} else if ( rval == 0) {
			log_("Ending connection.");
			throw connectionEndException();
		} else {
			log_(std::string("Reading<--").append(buffer+(bufferSize-bytesToRead), rval));
		}
	}
	Message::MessageHeader hdr;
	memcpy(&hdr, buffer, bufferSize);
	delete [] buffer;
	return hdr;
}

std::string RealChannel::readData(int length) {
	//creating buffer
	int bufferSize = length;
	char* buffer = new char[bufferSize];
	for(int i=0; i<bufferSize; i++)
		buffer[i] = 0;
	int rval;

	for( int bytesToRead = bufferSize; bytesToRead > 0; bytesToRead-=rval) {
		log_(std::string("Data bytes to read: ").append(std::to_string(bytesToRead)));
		rval = read(sock_, buffer+(bufferSize-bytesToRead), bytesToRead);
		if( rval == -1 ) {
			perror("reading stream message");
		} else if ( rval == 0) {
			log_("ending connection.");
			throw connectionEndException();
		} else {
			log_(std::string("Reading<--").append(buffer+(bufferSize-bytesToRead), rval));
		}
	}

	auto str = std::string(buffer, bufferSize);
	delete [] buffer;
	return str;
}

void RealChannel::handle(messages::pMessage msg) {
	Handlers::const_iterator iter = handlers_.find(msg->getCode());
	if(iter == handlers_.end() ) {
		log_(std::string("No handler for message code: ").append( std::to_string( msg->getCode() ) ) );
	} else {
		(*(iter->second))(msg);
	}
}

} /* namespace channels */
} /* namespace proto */
} /* namespace comuactiv */
