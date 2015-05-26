/*
 * ProxyChannel.cpp
 *
 *  Created on: 25 May 2015
 *      Author: Jan Kumor
 */

#include "ProxyChannel.hpp"

#include <unistd.h>
#include <map>
#include <memory>
#include <utility>


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
}

bool ProxyChannel::start() {
	if( !started() ) {
		return isStarted_ = getChannel()->start();
	}
	else {
		log_("Channel already started.");
		return false;
	}
}

void ProxyChannel::switchMode() {
	log_(std::string("Switching mode from ").append(mode_==ACTIVE?"ACTIVE to PASSIVE":"PASSIVE to ACTIVE"));
	sock_ = getChannel()->getSock();
	real_.reset();
	isStarted_ = false;
	handlers_.clear();

	switch(mode_) {
	case ACTIVE:
		mode_ = PASSIVE;
		break;

	case PASSIVE:
		mode_ = ACTIVE;
		break;
	}
}

void ProxyChannel::writeMessage(messages::pRawMessage msg) {
	if(started())
		getChannel()->writeMessage(msg);
	else
		log_("Channel not started");
}

void ProxyChannel::writeAndHandleMessage(messages::pRawMessage msg) {
	if(started())
		getChannel()->writeAndHandleMessage(msg);
	else
		log_("Channel not started");
}

pMessage ProxyChannel::readMessage() {
	if(started())
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
	//log_("Real Channel access.");
	if( !real_ ) {
		log_("Real Channel creation.");
		real_ = pRealChannel(new RealChannel(id_, mode_, handlers_, host_, port_, sock_) );
	}
	return real_;
}

} /* namespace channels */
} /* namespace proto */
} /* namespace comuactiv */
