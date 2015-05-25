/*
 * ComuactivClientSlot.cpp
 *
 *  Created on: 4 May 2015
 *      Author: Jan Kumor
 */

#include <comuactiv/ComuactivClientSlot.hpp>
#include <algorithm>
#include <iostream>
#include <memory>

#include "channels/Channel.hpp"
#include "channels/ProxyChannel.hpp"
#include "handlers/AssociationSetupResponseHandler.hpp"
#include "handlers/Handler.hpp"
#include "messages/AssociationSetupMsg.hpp"
#include "messages/Message.hpp"
#include "utils/Printer.hpp"

using namespace comuactiv::proto;
using namespace comuactiv::proto::messages;
using namespace comuactiv::proto::handlers;
using namespace comuactiv::proto::channels;
using namespace comuactiv::proto::utils;

namespace comuactiv {
namespace proto {

class ComuactivClientSlot::ComuactivClientSlotImpl {
public:
	ComuactivClientSlotImpl(std::string host, std::string highPort);
	void run();

private:
	Printer log_;

	std::string host_;
	std::string highPort_;
	std::string mediumPort_;
	std::string lowPort_;

	//high is active at connection association then turns passive
	ProxyChannel high_;

	//medium is sending event notifiers to CE so it is active
	pChannel Medium_;

	//low must be asynchronous therefore active and passive channels
	ProxyChannel aLow_;
	ProxyChannel pLow_;
};

ComuactivClientSlot::ComuactivClientSlot(std::string host, std::string highPort)
: slot_( new ComuactivClientSlotImpl(host, highPort) ) {
	// do nothing
}

ComuactivClientSlot::ComuactivClientSlotImpl::ComuactivClientSlotImpl(std::string host, std::string highPort)
: log_(std::string("ComuactivClientSlot#")),
  host_(host),
  highPort_(highPort) {
	log_("created.");
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
	log_("Creating passive channels");
	pLow_ = ProxyChannel(Channel::PASSIVE);
	pLow_.start();

	log_(std::string("Initialising connection to: ").append(host_).append(std::string(":")).append(highPort_));

	high_ = ProxyChannel(Channel::ACTIVE);
	high_.registerHandler(messages::Message::ASSOCIATION_SETUP_RESPONSE, pHandler(new AssociationSetupResponseHandler()) );
	high_.setPort("5555");

	high_.start();

	pMessage msg = pAssociationSetupMsg( new AssociationSetupMsg( std::string("6666"), std::string("6667") ) );
	log_("Writing ASSOCIATION_SETUP to high.");
	high_.writeMessage(msg->getRaw());

	high_.readMessage();
}

} /* namespace proto */
} /* namespace comuactiv */
