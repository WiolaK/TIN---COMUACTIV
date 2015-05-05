/*
 * Channel.cpp
 *
 *  Created on: 4 May 2015
 *      Author: Jan Kumor
 */

#include "Channel.hpp"

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <iostream>

using namespace comuactiv::proto;

namespace comuactiv {
namespace proto {

int Channel::counter_ = 0;

Channel::Channel(int sock, ChannelMode mode)
: sock_(sock), mode_(mode) {
	// This should be moved out of the constructor because this
	// may (will?) be accessed before the constructor has finished.
	// Because action is virtual, you can move this to a new member
	// function of Base. This also means tid can be private.
	id_ = ++counter_;
	pthread_create(&tid, nullptr, &execute, this);
}

Channel::~Channel() {
	close(sock_);
	pthread_join(tid, nullptr);
}

void* Channel::run() {
	std::cout << "Starting thread. Channel #" << counter_ << " on socket: "<< sock_ << std::endl;
	switch( mode_ ) {
	case ACTIVE:
		while(1) {
			std::cout << "Channel #" << id_ << std::endl;
			sleep(5);
		}
		break;

	case PASSIVE:
		while(1)
		{
			std::cout << "Channel #" << id_ << std::endl;
			sleep(5);
		}

		break;
	}
	return nullptr;
}

} /* namespace proto */
} /* namespace comuactiv */
