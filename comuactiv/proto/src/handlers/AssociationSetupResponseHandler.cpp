/*
 * AssociationSetupResponseHandler.cpp
 *
 *  Created on: 25 May 2015
 *      Author: Jan Kumor
 */

#include "AssociationSetupResponseHandler.hpp"

#include <memory>

#include "../messages/AssociationSetupResponseMsg.hpp"
#include "../utils/Printer.hpp"

using namespace comuactiv::proto::messages;

namespace comuactiv {
namespace proto {
namespace handlers {

AssociationSetupResponseHandler::AssociationSetupResponseHandler() {
	// TODO Auto-generated constructor stub
}

AssociationSetupResponseHandler::~AssociationSetupResponseHandler() {
	// TODO Auto-generated destructor stub
}

void AssociationSetupResponseHandler::operator ()(pMessage msg) {
	//utils::Printer("AssociationSetupResponseHandler")("executed");
	pAssociationSetupResponseMsg aSRMsg = std::static_pointer_cast<AssociationSetupResponseMsg>(msg);

	callback_(aSRMsg->getMediumPort(), aSRMsg->getLowPort());
}

} /* namespace handlers */
} /* namespace proto */
} /* namespace comuactiv */
