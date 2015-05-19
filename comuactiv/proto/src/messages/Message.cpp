/*
 * Message.cpp
 *
 *  Created on: 4 May 2015
 *      Author: Jan Kumor
 */

#include "Message.hpp"

namespace comuactiv {
namespace proto {
namespace messages {

uint32_t Message::counter_ = 0;

Message::Message(MsgCode code) {
	memcpy(header_.prefix_, "COMUACTIV15\0", 12);
	header_.code_ = code;
	header_.length_ = getLength();
	header_.id_ = counter_++;
	validLength_ = false;
}

Message::~Message() {
	// Do nothing
}

pRawMessage Message::getRaw() {
	pRawMessage raw = pRawMessage(new RawMessage(getLength()));

	//copying header
	memcpy(raw->array, &header_, sizeof(header_));

	//copying data
	if(data_.size() > 0 ) {
		memcpy(raw->array+sizeof(header_), data_.c_str(), data_.size());
	}

	//writing ending NUL
	raw->array[raw->length-1] = '\0';

	return raw;
}

} /* namespace messages */
} /* namespace proto */
} /* namespace comuactiv */
