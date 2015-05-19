/*
 * ComuactivServerSlot.cpp
 *
 *  Created on: 4 May 2015
 *      Author: Jan Kumor
 */

#include <comuactiv/ComuactivServerSlot.hpp>
#include <algorithm>
#include <iostream>
#include <memory>
#include <string>

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
	int sock_;

	std::string host_;
	std::string highPort_;
	std::string mediumPort_;
	std::string lowPort_;

	//high is initialized as passive then after association turns into active
	pAChannel aHigh_;

	//medium is always listening for events from FE therefore passive
	pPChannel pMedium_;

	//low must be asynchronous therefore active and passive
	pPChannel pLow_;
	pAChannel aLow_;
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
  sock_(sock),
  pMedium_(new PassiveChannel(5556, false)),
  pLow_(new PassiveChannel(5557, false)) {
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
	pPChannel pHigh = pPChannel(new PassiveChannel(sock_, true));
}

} /* namespace proto */
} /* namespace comuactiv */

