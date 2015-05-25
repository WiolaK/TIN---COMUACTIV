/*
 * Handler.hpp
 *
 *  Created on: 25 May 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_SRC_HANDLERS_HANDLER_HPP_
#define PROTO_SRC_HANDLERS_HANDLER_HPP_

#include <memory>

#include "../messages/Message.hpp"

namespace comuactiv {
namespace proto {
namespace handlers {

class Handler {
public:
	Handler() {};
	virtual ~Handler() {};

	virtual void operator()(messages::pMessage msg) = 0;
};

typedef std::shared_ptr<Handler> pHandler;

} /* namespace handlers */
} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_HANDLERS_HANDLER_HPP_ */
