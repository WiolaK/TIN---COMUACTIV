/*
 * AssociationSetupResponseHandler.hpp
 *
 *  Created on: 25 May 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_SRC_HANDLERS_ASSOCIATIONSETUPRESPONSEHANDLER_HPP_
#define PROTO_SRC_HANDLERS_ASSOCIATIONSETUPRESPONSEHANDLER_HPP_

#include "Handler.hpp"

namespace comuactiv {
namespace proto {
namespace handlers {

class AssociationSetupResponseHandler : public Handler {
public:
	AssociationSetupResponseHandler();
	virtual ~AssociationSetupResponseHandler();

	virtual void operator()(messages::pMessage msg) {
		std::cout << "RESPONSE HANDLER" << std::endl;
	}
};

} /* namespace handlers */
} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_HANDLERS_ASSOCIATIONSETUPRESPONSEHANDLER_HPP_ */
