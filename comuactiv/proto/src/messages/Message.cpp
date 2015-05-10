/*
 * Message.cpp
 *
 *  Created on: 4 May 2015
 *      Author: Jan Kumor
 */

#include "Message.hpp"

#include <cereal/cereal.hpp>
namespace comuactiv {
namespace proto {
namespace messages {

Message::Message() {
	//Do nothing
}

Message::Message( MsgCode code)
: prefix_(std::string("COMUACTIV")),
  code_(code),
  length_(0),
  id_(0) {
	// Do nothing
}

Message::~Message() {
	// Do nothing
}

} /* namespace messages */
} /* namespace proto */
} /* namespace comuactiv */
