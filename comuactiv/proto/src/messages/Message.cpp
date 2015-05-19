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

/*
Message::Message() {
	//Do nothing
}
*/

uint32_t Message::counter_ = 0;

Message::~Message() {
	// Do nothing
}

} /* namespace messages */
} /* namespace proto */
} /* namespace comuactiv */
