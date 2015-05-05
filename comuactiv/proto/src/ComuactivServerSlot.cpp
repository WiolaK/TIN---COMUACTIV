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

#include <ComuactivServerSlot.hpp>
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

class ComuactivServerSlot::ComuactivServerSlotImpl {
public:
	ComuactivServerSlotImpl();
	ComuactivServerSlotImpl(int sock);
	void run();

private:
	char* host_;
	char* highPort_;
	char* mediumPort_;
	char* lowPort_;
	pAChannel aHigh_;
	pAChannel aMedium_;
	pAChannel aLow_;
	pPChannel pHigh_;
	pPChannel pMedium_;
	pPChannel pLow_;
};

ComuactivServerSlot::ComuactivServerSlot()
: slot_(new ComuactivServerSlotImpl()) {
	// do nothing
}

ComuactivServerSlot::ComuactivServerSlot(int sock)
: slot_(new ComuactivServerSlotImpl(sock)) {
	// do nothing
}

ComuactivServerSlot::ComuactivServerSlotImpl::ComuactivServerSlotImpl() {

}

ComuactivServerSlot::ComuactivServerSlotImpl::ComuactivServerSlotImpl(int sock)
: pHigh_(new PassiveChannel(sock)),
  pMedium_(new PassiveChannel()),
  pLow_(new PassiveChannel()) {
	std::cout << "Creating COMUACTIV ServerSlot" << std::endl;
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
	std::cin >> highPort_;

	std::cin >> mediumPort_;
	std::cin >> lowPort_;
}

} /* namespace proto */
} /* namespace comuactiv */

