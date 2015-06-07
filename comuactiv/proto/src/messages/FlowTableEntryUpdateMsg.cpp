/*
 * FlowTableEntryUpdateMsg.cpp
 *
 *  Created on: 10 May 2015
 *      Author: Jan Kumor
 */

#include "FlowTableEntryUpdateMsg.hpp"

namespace comuactiv {
namespace proto {
namespace messages {

FlowTableEntryUpdateMsg::FlowTableEntryUpdateMsg(std::string tableString)
: Message(defaultCode) {
	this->setData(tableString);
}

FlowTableEntryUpdateMsg::FlowTableEntryUpdateMsg(pRawMessage raw)
: Message(defaultCode) {
	// TODO Auto-generated constructor stub

}

FlowTableEntryUpdateMsg::~FlowTableEntryUpdateMsg() {
	// TODO Auto-generated destructor stub
}

} /* namespace messages */
} /* namespace proto */
} /* namespace comuactiv */
