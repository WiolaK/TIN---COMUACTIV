/*
 * ProxyChannel.cpp
 *
 *  Created on: 25 May 2015
 *      Author: Jan Kumor
 */

#include "ProxyChannel.hpp"

#include <map>
#include <memory>
#include <utility>

#include "../utils/Printer.hpp"

using namespace comuactiv::proto::messages;
using namespace comuactiv::proto::handlers;
using namespace comuactiv::proto::utils;

namespace comuactiv {
namespace proto {
namespace channels {

int ProxyChannel::counter_ = 0;

ProxyChannel::ProxyChannel(ChannelMode mode)
: id_(++counter_),
  log_(std::string("ProxyChannel#").append(std::to_string(id_))),
  isStarted_(false),
  mode_(mode),
  port_("0"),
  sock_(-1) {

}
ProxyChannel::~ProxyChannel() {
	// TODO Auto-generated destructor stub
}

bool ProxyChannel::start() {
	if( !isStarted_ ) {
		log_("PROXY START");
		isStarted_ = getChannel()->start();
		return isStarted_;
	}
	else {
		log_("Channel already started.");
		return false;
	}
}

void ProxyChannel::writeMessage(messages::pRawMessage msg) {
	if(isStarted_)
		getChannel()->writeMessage(msg);
	else
		log_("Channel not started");
}

void ProxyChannel::writeAndHandleMessage(messages::pRawMessage msg) {
	if(isStarted_)
		getChannel()->writeAndHandleMessage(msg);
	else
		log_("Channel not started");
}

pMessage ProxyChannel::readMessage() {
	if(isStarted_)
		return getChannel()->readMessage();
	else {
		log_("Channel not started");
		return pMessage(nullptr);
	}
}

bool ProxyChannel::registerHandler(Message::MsgCode code, pHandler handler) {
	return ( handlers_.insert( std::pair<Message::MsgCode, pHandler>(code, handler) ) ).second;
}

pRealChannel ProxyChannel::getChannel() const {
	log_("GET CHANNEL");
	if( !real_ ) {
		log_("REAL CREATION");
		real_ = pRealChannel(new RealChannel(id_, mode_, handlers_, port_, sock_) );
	}
	return real_;
}

} /* namespace channels */
} /* namespace proto */
} /* namespace comuactiv */