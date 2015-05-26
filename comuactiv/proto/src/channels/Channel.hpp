/*
 * Channel.hpp
 *
 *  Created on: 25 May 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_SRC_CHANNELS_CHANNEL_HPP_
#define PROTO_SRC_CHANNELS_CHANNEL_HPP_

#include <map>
#include <memory>

#include "../handlers/Handler.hpp"
#include "../messages/Message.hpp"
#include "../messages/RawMessage.hpp"

namespace comuactiv {
namespace proto {
namespace channels {

class Channel {
public:
	enum ChannelMode {
		PASSIVE,
		ACTIVE
	};

	virtual ~Channel() {}; //body for optimisation issues

	virtual bool start() = 0;
	virtual void writeMessage(messages::pRawMessage msg) = 0;
	virtual void writeAndHandleMessage(messages::pRawMessage msg) = 0;
	virtual messages::pMessage readMessage() = 0;

	virtual std::string getHost() const = 0;
	virtual std::string getPort() const = 0;
	virtual int getSock() const = 0;

	//virtual void switchMode() = 0;

	typedef	std::map<messages::Message::MsgCode, handlers::pHandler> Handlers;

};

/**
 * Sprytny wskaźnik na interfejs Channel.
 */
typedef std::shared_ptr<Channel> pChannel;

} /* namespace channels */
} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_CHANNELS_CHANNEL_HPP_ */
