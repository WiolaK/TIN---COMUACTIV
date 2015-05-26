/*
 * EventNotificationHandler.hpp
 *
 *  Created on: 26 May 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_SRC_HANDLERS_EVENTNOTIFICATIONHANDLER_HPP_
#define PROTO_SRC_HANDLERS_EVENTNOTIFICATIONHANDLER_HPP_

#include "Handler.hpp"

namespace comuactiv {
namespace proto {
namespace handlers {

class EventNotificationHandler: public Handler {
public:
	EventNotificationHandler();
	virtual ~EventNotificationHandler();

	virtual void operator()(messages::pMessage msg) {
		std::cout << "EVENT!" << std::endl;
	}
};

} /* namespace handlers */
} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_HANDLERS_EVENTNOTIFICATIONHANDLER_HPP_ */
