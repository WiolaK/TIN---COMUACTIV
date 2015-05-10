/*
 * ComuactivServerSlot.cpp
 *
 *  Created on: 4 May 2015
 *      Author: Jan Kumor
 */

#include <algorithm>
#include <iostream>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <memory>
#include <cstring>

#include <comuactiv/ComuactivServerSlot.hpp>
#include "ActiveChannel.hpp"
#include "PassiveChannel.hpp"


using namespace comuactiv::proto;

namespace comuactiv {
namespace proto {

typedef struct sockaddr_in SocketAddressIn;
typedef struct sockaddr SocketAddress;
typedef struct hostent HostEntry;
typedef std::shared_ptr<ActiveChannel> pAChannel;
typedef std::shared_ptr<PassiveChannel> pPChannel;

#define LOG(x) std::cout << "COMUACTIVE ServerSlot #" << id_ << ": " << x << std::endl

class ComuactivServerSlot::ComuactivServerSlotImpl {
public:
	static int counter_;

	ComuactivServerSlotImpl();
	ComuactivServerSlotImpl(int sock);
	void run();

private:
	int id_;
	std::string host_;
	std::string highPort_;
	std::string mediumPort_;
	std::string lowPort_;
	pAChannel aHigh_;
	pAChannel aMedium_;
	pAChannel aLow_;
	pPChannel pHigh_;
	pPChannel pMedium_;
	pPChannel pLow_;
};

int ComuactivServerSlot::ComuactivServerSlotImpl::counter_ = 0;

ComuactivServerSlot::ComuactivServerSlot()
: slot_(new ComuactivServerSlotImpl()) {
	// do nothing
}

ComuactivServerSlot::ComuactivServerSlot(int sock)
: slot_(new ComuactivServerSlotImpl(sock)) {
	// do nothing
}

ComuactivServerSlot::ComuactivServerSlotImpl::ComuactivServerSlotImpl()
: id_(++counter_) {

}

ComuactivServerSlot::ComuactivServerSlotImpl::ComuactivServerSlotImpl(int sock)
: id_(++counter_),
  pHigh_(new PassiveChannel(sock)),
  pMedium_(new PassiveChannel()),
  pLow_(new PassiveChannel()) {
	LOG("created.");
}

/*
ComuactivSlot::ComuactivSlot(const ComuactivSlot& other)
    : slot_(new ComuactivSlot(*other.slot_)) {
    // do nothing
}*/

ComuactivServerSlot::ComuactivServerSlot(ComuactivServerSlot&& other)
: slot_(0)
{
	std::swap(slot_, other.slot_);
}

ComuactivServerSlot& ComuactivServerSlot::operator=(const ComuactivServerSlot &other) {
	if(this != &other) {
		*slot_ = *(other.slot_);
	}
	return *this;
}

ComuactivServerSlot::~ComuactivServerSlot() {
	delete slot_;
}

void ComuactivServerSlot::run() {
	slot_->run();
}

void ComuactivServerSlot::ComuactivServerSlotImpl::run() {
	sleep(1);
	host_ = std::string("127.0.0.1");
	LOG("Input high port: ");
	std::cin>>highPort_;
	LOG("Initialising connection to: " << host_ << ":" << highPort_);
	aHigh_ = pAChannel(new ActiveChannel(host_, highPort_));
	sleep(1);
	LOG("Input medium port: ");
	std::cin>>mediumPort_;
	LOG("Initialising connection to: " << host_ << ":" << mediumPort_);
	aMedium_ = pAChannel(new ActiveChannel(host_, mediumPort_));
	LOG("Input low port: ");
	std::cin>>lowPort_;
	LOG("Initialising connection to: " << host_ << ":" << lowPort_);
	aLow_ = pAChannel(new ActiveChannel(host_, lowPort_));
	while(true) {
		LOG("Writing to high");
		aHigh_->writeData("H");
		sleep(1);
		LOG("Writing to medium");
		aMedium_->writeData("M");
		sleep(1);
		LOG("Writing to low");
		aLow_->writeData("L");
		sleep(1);
	}
}

} /* namespace proto */
} /* namespace comuactiv */

