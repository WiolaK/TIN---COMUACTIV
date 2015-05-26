/*
 * AssociationSetupHandler.hpp
 *
 *  Created on: 25 May 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_SRC_HANDLERS_ASSOCIATIONSETUPHANDLER_HPP_
#define PROTO_SRC_HANDLERS_ASSOCIATIONSETUPHANDLER_HPP_

#include <functional>
#include <string>

#include "../channels/ProxyChannel.hpp"
#include "../messages/Message.hpp"
#include "Handler.hpp"

namespace comuactiv {
namespace proto {
class ComuactivServerSlot;
} /* namespace proto */
} /* namespace comuactiv */

namespace comuactiv {
namespace proto {
namespace handlers {

class AssociationSetupHandler: public Handler {
public:
	typedef std::function<void(std::string)> Callback;

	//AssociationSetupHandler(channels::ProxyChannel& high) : high_(high) {};
	AssociationSetupHandler(Callback callback) : callback_(callback) {};
	virtual ~AssociationSetupHandler();

	virtual void operator()(messages::pMessage msg);

private:
	//channels::ProxyChannel& high_;
	Callback callback_;
};

} /* namespace handlers */
} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_HANDLERS_ASSOCIATIONSETUPHANDLER_HPP_ */
