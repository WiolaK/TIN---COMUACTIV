/*
 * HeartbeatHandler.hpp
 *
 *  Created on: 26 May 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_SRC_HANDLERS_HEARTBEATHANDLER_HPP_
#define PROTO_SRC_HANDLERS_HEARTBEATHANDLER_HPP_

#include <iostream>

#include "../messages/Message.hpp"
#include "Handler.hpp"

namespace comuactiv {
namespace proto {
namespace handlers {

class HeartbeatHandler: public Handler {
public:
	HeartbeatHandler();
	virtual ~HeartbeatHandler();

	virtual void operator()(messages::pMessage msg) {
		std::cout << "HEARTBEAT HANDLER" << std::endl;
	}
};

} /* namespace handlers */
} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_HANDLERS_HEARTBEATHANDLER_HPP_ */
