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
		log_("PASSIVE START");
		if(pthread_create(&tid, nullptr, &execute, this)) {
			log_(std::string("pthread_create failure errno=").append(std::to_string(errno)));
			return false;
		}
		break;

	case ACTIVE:
		log_("ACTIVE START");
		initializeActive();
		break;

	}
	return true;

}

void* RealChannel::run() {
	log_("RUN");
	if( sock_ == -1) {
		log_("SOCK == -1");
		initializePassive();
	}
	workPassive();
	log_("work stopped.");
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
	log_(std::string("initialising on socket: ").append(std::to_string(sock_)));
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
	log_(std::string("port: ").append(std::to_string(ntohs(serverAddress.sin_port))));
	port_ = std::to_string(ntohs(serverAddress.sin_port));

	listen(sock_, 1);
	log_("is listening really hard ^^");

	sock_ = accept(sock_,(struct sockaddr*) 0,(unsigned int*) 0);
	if (sock_ == -1 ) {
		perror("accept");
	} else {
		log_(std::string("incoming connection accepted on port: ").append(port_));
	}
}

void RealChannel::workPassive() {
	log_("work started.");
	while(true) {
		pMessage msg( new Message() );
		try {
			pMessage msg = readMessage();
			handle(MessageFactory::getInstance().create(msg->getHeader().code_, msg->getRaw()));
		} catch(const connectionEndException& e) {
			break;
		}
	}
}

void RealChannel::writeMessage(pRawMessage msg) {
	log_(std::string("writing: ").append(std::string(msg->array, msg->length)));

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
	handle(response);
}

pMessage RealChannel::readMessage() {
	pMessage msg(new Message());
	msg->setHeader(readHeader());
	msg->setData( readData( msg->getHeader().length_-sizeof(Message::MessageHeader) ) );
	return msg;
}

void RealChannel::readAndHandleMessage() {
	auto msg = readMessage();
	handle(msg);
}

Message::MessageHeader RealChannel::readHeader() {
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
			log_("ending connection.");
			throw connectionEndException();
		} else {
			log_(std::string(buffer+(bufferSize-bytesToRead), rval));
		}
	}
	Message::MessageHeader hdr;
	memcpy(&hdr, buffer, bufferSize);
	delete [] buffer;
	return hdr;
}

void RealChannel::handle(messages::pMessage msg) {
	Handlers::const_iterator iter = handlers_.find(msg->getCode());
	if(iter == handlers_.end() ) {
		std::cout << "NO HANDLER FOR: " << msg->getCode() << std::endl;
	} else {
		(*(iter->second))(msg);
	}
}

std::string RealChannel::readData(int length) {
	//creating buffer
	int bufferSize = length;
	char* buffer = new char[bufferSize];
	for(int i=0; i<bufferSize; i++)
		buffer[i] = 0;
	int rval;

	for( int bytesToRead = bufferSize; bytesToRead > 0 && rval != 0; bytesToRead-=rval) {
		log_(std::string("Bytes to read: ").append(std::to_string(bytesToRead)));
		rval = read(sock_, buffer+(bufferSize-bytesToRead), bytesToRead);
		if( rval == -1 ) {
			perror("reading stream message");
		} else if ( rval == 0) {
			log_("ending connection.");
			throw connectionEndException();
		} else {
			log_(std::string(buffer+(bufferSize-bytesToRead), rval));
		}
	}

	auto str = std::string(buffer, bufferSize);
	delete [] buffer;
	return str;
}

} /* namespace channels */
} /* namespace proto */
} /* namespace comuactiv */
