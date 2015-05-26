/*
 * AssociationSetupHandler.hpp
 *
 *  Created on: 25 May 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_SRC_HANDLERS_ASSOCIATIONSETUPHANDLER_HPP_
#define PROTO_SRC_HANDLERS_ASSOCIATIONSETUPHANDLER_HPP_

#include "../../include/comuactiv/ComuactivServerSlot.hpp"
#include "../messages/Message.hpp"
#include "Handler.hpp"

namespace comuactiv {
namespace proto {
namespace handlers {

class AssociationSetupHandler: public Handler {
public:
	AssociationSetupHandler() {};
	virtual ~AssociationSetupHandler();

	virtual void operator()(messages::pMessage msg);

private:

};

} /* namespace handlers */
} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_HANDLERS_ASSOCIATIONSETUPHANDLER_HPP_ */
