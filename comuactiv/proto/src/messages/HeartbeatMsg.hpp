/*
 * HeartbeatMsg.hpp
 *
 *  Created on: 10 May 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_SRC_MESSAGES_HEARTBEATMSG_HPP_
#define PROTO_SRC_MESSAGES_HEARTBEATMSG_HPP_

#include <memory>

#include "Message.hpp"
#include "RawMessage.hpp"

namespace comuactiv {
namespace proto {
namespace messages {

class HeartbeatMsg: public Message {
public:
	const static MsgCode defaultCode = HEARTBEAT;

	HeartbeatMsg(pRawMessage raw);
	virtual ~HeartbeatMsg();

	static pMessage create(pRawMessage raw) {
		return pMessage(new HeartbeatMsg(raw));
	}
};

} /* namespace messages */
} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_MESSAGES_HEARTBEATMSG_HPP_ */
