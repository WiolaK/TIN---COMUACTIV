/*
 * AssociationSetupResponseHandler.hpp
 *
 *  Created on: 25 May 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_SRC_HANDLERS_ASSOCIATIONSETUPRESPONSEHANDLER_HPP_
#define PROTO_SRC_HANDLERS_ASSOCIATIONSETUPRESPONSEHANDLER_HPP_

#include <functional>
#include <string>

#include "../messages/Message.hpp"
#include "Handler.hpp"

namespace comuactiv {
namespace proto {
namespace handlers {

class AssociationSetupResponseHandler : public Handler {
public:
	typedef std::function<void(std::string, std::string)> Callback;
	AssociationSetupResponseHandler();
	AssociationSetupResponseHandler( Callback callback) : callback_(callback) {};
	virtual ~AssociationSetupResponseHandler();

	virtual void operator()(messages::pMessage msg);

private:
	Callback callback_;
};

} /* namespace handlers */
} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_HANDLERS_ASSOCIATIONSETUPRESPONSEHANDLER_HPP_ */
