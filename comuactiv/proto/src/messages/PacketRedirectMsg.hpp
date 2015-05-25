/*
 * PacketRedirectMsg.hpp
 *
 *  Created on: 10 May 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_SRC_MESSAGES_PACKETREDIRECTMSG_HPP_
#define PROTO_SRC_MESSAGES_PACKETREDIRECTMSG_HPP_

#include "Message.hpp"

namespace comuactiv {
namespace proto {
namespace messages {

class PacketRedirectMsg: public Message {
public:
	const static MsgCode defaultCode = PACKET_REDIRECT;

	PacketRedirectMsg();
	virtual ~PacketRedirectMsg();
};

} /* namespace messages */
} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_MESSAGES_PACKETREDIRECTMSG_HPP_ */
