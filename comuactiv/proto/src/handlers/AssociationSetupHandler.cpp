/*
 * AssociationSetupHandler.cpp
 *
 *  Created on: 25 May 2015
 *      Author: Jan Kumor
 */

#include "AssociationSetupHandler.hpp"

#include <iostream>


using namespace comuactiv::proto::messages;

namespace comuactiv {
namespace proto {
namespace handlers {

AssociationSetupHandler::AssociationSetupHandler() {
	// TODO Auto-generated constructor stub

}

AssociationSetupHandler::~AssociationSetupHandler() {
	// TODO Auto-generated destructor stub
}

void AssociationSetupHandler::operator()(pMessage msg) {
	std::cout << "Handler!" << std::endl;
}

} /* namespace handlers */
} /* namespace proto */
} /* namespace comuactiv */
