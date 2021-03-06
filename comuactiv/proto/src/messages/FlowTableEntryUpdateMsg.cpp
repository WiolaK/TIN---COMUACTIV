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
	memcpy(&header_, raw->array, sizeof(header_));
	//copying data
	int dataLength = header_.length_ - sizeof(header_);
	if( dataLength > 0 ) {
		data_.assign(raw->array+sizeof(header_), dataLength);
	}
}

FlowTableEntryUpdateMsg::~FlowTableEntryUpdateMsg() {
	// TODO Auto-generated destructor stub
}

} /* namespace messages */
} /* namespace proto */
} /* namespace comuactiv */
