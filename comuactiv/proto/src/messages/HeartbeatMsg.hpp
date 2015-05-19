/*
 * HeartbeatMsg.hpp
 *
 *  Created on: 10 May 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_SRC_MESSAGES_HEARTBEATMSG_HPP_
#define PROTO_SRC_MESSAGES_HEARTBEATMSG_HPP_

#include "Message.hpp"

namespace comuactiv {
namespace proto {
namespace messages {

class HeartbeatMsg: public Message {
public:
	const static MsgCode defaultCode = HEARTBEAT;

	HeartbeatMsg();
	virtual ~HeartbeatMsg();

	static Message* create() {
		return new HeartbeatMsg();
	}
};

} /* namespace messages */
} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_MESSAGES_HEARTBEATMSG_HPP_ */
