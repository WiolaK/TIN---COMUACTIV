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

Message::~Message() {
	// Do nothing
}

} /* namespace messages */
} /* namespace proto */
} /* namespace comuactiv */
