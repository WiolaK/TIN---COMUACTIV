/*
 * FlowTableEntryUpdateHandler.hpp
 *
 *  Created on: 25 May 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_SRC_HANDLERS_FLOWTABLEENTRYUPDATEHANDLER_HPP_
#define PROTO_SRC_HANDLERS_FLOWTABLEENTRYUPDATEHANDLER_HPP_

#include <functional>
#include <string>

#include "../../include/comuactiv/FlowTable.hpp"
#include "../messages/Message.hpp"
#include "Handler.hpp"

namespace comuactiv {
namespace proto {
namespace handlers {

class FlowTableEntryUpdateHandler : public Handler {
public:
	typedef std::function<void(std::string, std::string)> Callback;
	FlowTableEntryUpdateHandler(flowtable::pFlowTable table);
	virtual ~FlowTableEntryUpdateHandler();

	virtual void operator()(messages::pMessage msg);

private:
	flowtable::pFlowTable table_;
};

} /* namespace handlers */
} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_HANDLERS_FLOWTABLEENTRYUPDATEHANDLER_HPP_ */
