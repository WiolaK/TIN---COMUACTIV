/*
 * EventNotificationMsg.hpp
 *
 *  Created on: 10 May 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_SRC_MESSAGES_EVENTNOTIFICATIONMSG_HPP_
#define PROTO_SRC_MESSAGES_EVENTNOTIFICATIONMSG_HPP_

#include "Message.hpp"

namespace comuactiv {
namespace proto {
namespace messages {

class EventNotificationMsg: public Message {
public:
	const static MsgCode defaultCode = EVENT_NOTIFICATION;

	EventNotificationMsg();
	virtual ~EventNotificationMsg();
};

} /* namespace messages */
} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_MESSAGES_EVENTNOTIFICATIONMSG_HPP_ */
