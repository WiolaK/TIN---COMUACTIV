/*
 * AssociationSetupMsg.hpp
 *
 *  Created on: 10 May 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_SRC_MESSAGES_ASSOCIATIONSETUPMSG_HPP_
#define PROTO_SRC_MESSAGES_ASSOCIATIONSETUPMSG_HPP_

#include "Message.hpp"

namespace comuactiv {
namespace proto {
namespace messages {

class AssociationSetupMsg: public Message {
public:
	const static MsgCode defaultCode = ASSOCIATION_SETUP;

	AssociationSetupMsg();
	virtual ~AssociationSetupMsg();

	static Message* create() {
		return new AssociationSetupMsg();
	}
};

} /* namespace messages */
} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_MESSAGES_ASSOCIATIONSETUPMSG_HPP_ */
