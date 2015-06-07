/*
 * FlowTableEntryUpdateMsg.hpp
 *
 *  Created on: 10 May 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_SRC_MESSAGES_FLOWTABLEENTRYUPDATEMSG_HPP_
#define PROTO_SRC_MESSAGES_FLOWTABLEENTRYUPDATEMSG_HPP_

#include <memory>

#include "Message.hpp"
#include "RawMessage.hpp"

namespace comuactiv {
namespace proto {
namespace messages {

class FlowTableEntryUpdateMsg: public Message {
public:
	const static MsgCode defaultCode = FLOW_TABLE_ENTRY_UPDATE;

	FlowTableEntryUpdateMsg(std::string tableString);
	FlowTableEntryUpdateMsg(pRawMessage raw);
	virtual ~FlowTableEntryUpdateMsg();

	pMessage create(pRawMessage raw) {
		return std::shared_ptr<FlowTableEntryUpdateMsg>( new FlowTableEntryUpdateMsg(raw) );
	}
};

typedef std::shared_ptr<FlowTableEntryUpdateMsg> pFlowTableEntryUpdateMsg;

} /* namespace messages */
} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_MESSAGES_FLOWTABLEENTRYUPDATEMSG_HPP_ */
