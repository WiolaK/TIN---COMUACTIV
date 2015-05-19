/*
 * ComuactivClientSlot.cpp
 *
 *  Created on: 4 May 2015
 *      Author: Jan Kumor
 */

#include <comuactiv/ComuactivClientSlot.hpp>
#include <unistd.h>
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <memory>

#include "ActiveChannel.hpp"
#include "comuactiv_utils.hpp"
#include "messages/Message.hpp"
#include "messages/MessageFactory.hpp"
#include "PassiveChannel.hpp"

#define DATA "Some msg"

#define LOG(x) std::cout << "COMUACTIVE ClientSlot: " << x << std::endl

using namespace comuactiv::proto;
using namespace comuactiv::proto::messages;

namespace comuactiv {
namespace proto {

class ComuactivClientSlot::ComuactivClientSlotImpl {
public:
	ComuactivClientSlotImpl(std::string host, std::string highPort);
	void run();

private:
	std::string host_;
	std::string highPort_;
	std::string mediumPort_;
	std::string lowPort_;

	//high is active at connection association then turns passive
	pPChannel pHigh_;

	//medium is sending event notifiers to CE so it is active
	pAChannel aMedium_;

	//low must be asynchronous therefore active and passive channels
	pAChannel aLow_;
	pPChannel pLow_;
};

ComuactivClientSlot::ComuactivClientSlot(std::string host, std::string highPort)
: slot_( new ComuactivClientSlotImpl(host, highPort) ) {
	// do nothing
}

ComuactivClientSlot::ComuactivClientSlotImpl::ComuactivClientSlotImpl(std::string host, std::string highPort)
: host_(host),
  highPort_(highPort) {
	LOG("created.");
}
/*
ComuactivSlot::ComuactivSlot(const ComuactivSlot& other)
    : slot_(new ComuactivSlot(*other.slot_)) {
    // do nothing
}*/

ComuactivClientSlot::ComuactivClientSlot(ComuactivClientSlot&& other)
: slot_(nullptr)
{
	std::swap(slot_, other.slot_);
}

ComuactivClientSlot& ComuactivClientSlot::operator=(const ComuactivClientSlot &other) {
	if(this != &other) {
		*slot_ = *(other.slot_);
	}
	return *this;
}

ComuactivClientSlot::~ComuactivClientSlot() {
	delete slot_;
}

void ComuactivClientSlot::run() {
	slot_->run();
}

void ComuactivClientSlot::ComuactivClientSlotImpl::run() {
	LOG("Creating passive channels");
	pHigh_ = pPChannel(new PassiveChannel(6666, false));
	pLow_ = pPChannel(new PassiveChannel(6667, false));

	LOG("Initialising connection to: " << host_ << ":" << highPort_);
	{
		pAChannel aHigh = pAChannel(new ActiveChannel(host_, highPort_));
		MessageFactory::getInstance().initialize();
		pMessage msg = MessageFactory::getInstance().create(Message::ASSOCIATION_SETUP);
		msg->setData("6666\n 6667\n");
		LOG("Writing ASSOCIATION_SETUP to high.");
		aHigh->writeMessage(msg->getRaw());
		aHigh->listenResponse();
	}


}

} /* namespace proto */
} /* namespace comuactiv */
