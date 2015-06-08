/*
 * AssociationSetupHandler.cpp
 *
 *  Created on: 25 May 2015
 *      Author: Jan Kumor
 */

#include "AssociationSetupHandler.hpp"

#include <unistd.h>
#include <iostream>
#include <memory>

#include "../messages/AssociationSetupMsg.hpp"
#include "../utils/Printer.hpp"


using namespace comuactiv::proto::messages;

namespace comuactiv {
namespace proto {
namespace handlers {

AssociationSetupHandler::~AssociationSetupHandler() {
	// TODO Auto-generated destructor stub
}

void AssociationSetupHandler::operator()(pMessage msg) {
	//utils::Printer("AssociationSetupHandler")("executed");
	std::cout << "AssociationSetup Handler" << std::endl;
	pAssociationSetupMsg aSMsg = std::static_pointer_cast<AssociationSetupMsg>(msg);
	sleep(2);
	/*pMessage response = pAssociationSetupResponseMsg( new AssociationSetupResponseMsg( std::string("5554"), std::string("5553") ) );
	high_.writeMessage(response->getRaw());*/
	callback_(aSMsg->getLowPort());
}

} /* namespace handlers */
} /* namespace proto */
} /* namespace comuactiv */
