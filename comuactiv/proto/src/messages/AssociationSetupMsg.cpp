/*
 * AssociationSetupMsg.cpp
 *
 *  Created on: 10 May 2015
 *      Author: Jan Kumor
 */

#include "AssociationSetupMsg.hpp"

#include <string>

namespace comuactiv {
namespace proto {
namespace messages {

AssociationSetupMsg::AssociationSetupMsg()
: Message(defaultCode) {
}

AssociationSetupMsg::~AssociationSetupMsg() {
	// Do nothing
}

} /* namespace messages */
} /* namespace proto */
} /* namespace comuactiv */
