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

	virtual bool start();
	void switchMode();

	virtual void writeMessage(messages::pRawMessage msg);
	virtual void writeAndHandleMessage(messages::pRawMessage msg);
	virtual messages::pMessage readMessage();

	bool registerHandler(messages::Message::MsgCode code, handlers::pHandler handler);

	virtual std::string getPort() const {
		if(started()) {
			return getChannel()->getPort();
		} else {
			return port_;
		}
	}

	void setPort(const std::string& port) {
		port_.assign(port);
	}

	virtual std::string getHost() const {
		if(started()) {
			return getChannel()->getPort();
		} else {
			return port_;
		}
	}

	void setHost(const std::string host) {
		host_ = host;
	}

	virtual int getSock() const {
		if(started()) {
			return getChannel()->getSock();
		} else {
			return sock_;
		}
	}

	void setSock(const int& sock) {
		sock_ = sock;
	}

	//TODO move started to Real and proxy to it
	bool started() const {
		//log_(std::string("STARTED?").append(std::to_string(isStarted_)));
		return isStarted_;
	}

private:
	int id_;
	utils::Printer log_;

	mutable pRealChannel real_;
	bool isStarted_;

	ChannelMode mode_;
	Handlers handlers_;

	std::string host_;
	std::string port_;
	int sock_;

	pRealChannel getChannel() const;
};

} /* namespace channels */
} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_CHANNELS_PROXYCHANNEL_HPP_ */
