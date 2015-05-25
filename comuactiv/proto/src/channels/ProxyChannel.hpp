/*
 * ProxyChannel.hpp
 *
 *  Created on: 25 May 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_SRC_CHANNELS_PROXYCHANNEL_HPP_
#define PROTO_SRC_CHANNELS_PROXYCHANNEL_HPP_

#include <string>

#include "../handlers/Handler.hpp"
#include "../messages/Message.hpp"
#include "../messages/RawMessage.hpp"
#include "../utils/Printer.hpp"
#include "Channel.hpp"
#include "RealChannel.hpp"

namespace comuactiv {
namespace proto {
namespace channels {

class ProxyChannel: public Channel {
public:
	static int counter_;

	ProxyChannel() : log_(std::string("ProxyChannel#NULL")) { /*Do nothing*/ };
	ProxyChannel(ChannelMode mode);
	virtual ~ProxyChannel();

	virtual void start();

	virtual void writeMessage(messages::pRawMessage msg);

	virtual messages::pMessage readMessage();

	bool registerHandler(messages::Message::MsgCode code, handlers::pHandler handler);

	std::string getPort() const {
		return port_;
	}

	void setPort(const std::string& port) {
		port_.assign(port);
	}

	int getSock() const {
		return sock_;
	}

	void setSock(const int& sock) {
		sock_ = sock;
	}

private:
	int id_;
	utils::Printer log_;

	pRealChannel real_;
	bool isStarted_;

	ChannelMode mode_;
	Handlers handlers_;

	std::string port_;
	int sock_;

	pRealChannel getChannel();
};

} /* namespace channels */
} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_CHANNELS_PROXYCHANNEL_HPP_ */
