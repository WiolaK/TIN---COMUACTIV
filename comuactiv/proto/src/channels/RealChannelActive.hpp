/*
 * RealChannelActive.hpp
 *
 *  Created on: 4 May 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_SRC_CHANNELS_REALCHANNEL_HPP_
#define PROTO_SRC_CHANNELS_REALCHANNEL_HPP_

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <utility>

#include "../messages/Message.hpp"
#include "../messages/RawMessage.hpp"
#include "../utils/ThreadBase.hpp"
#include "Channel.hpp"

namespace comuactiv {
namespace proto {
namespace channels {

class RealChannelActive: public Channel {
public:
	RealChannelActive();
	RealChannelActive(int sock);
	RealChannelActive(int id, ChannelMode mode, Handlers handlers, std::string port, int sock): id_(id), mode_(mode), handlers_(handlers), port_(port), sock_(sock) {};
	virtual ~RealChannelActive();

	virtual void start();

	int getSock() const {
		return sock_;
	}

	virtual void writeMessage(messages::pRawMessage msg);
	virtual messages::pMessage readMessage();

	void handle(messages::pMessage msg) {
		Handlers::const_iterator iter = handlers_.find(msg->getCode());
		if(iter == handlers_.end() ) {
			std::cout << "NO HANDLER FOR:" << msg->getCode() << std::endl;
		} else {
			(*(iter->second))(msg);
		}
	}

private:
	int id_;
	ChannelMode mode_;
	Handlers handlers_;

	std::string port_;
	int sock_;
	std::string host_;

	messages::Message::MessageHeader readHeader();
	std::string readData(int length_);
	void initializeActive();
};

/**
 * Sprytny wskaźnik na typ RealChannelActive.
 */
typedef std::shared_ptr<RealChannelActive> pRealChannelActive;

} /* namespace channels */
} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_CHANNELS_REALCHANNEL_HPP_ */
