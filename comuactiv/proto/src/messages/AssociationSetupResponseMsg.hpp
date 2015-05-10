/*
 * AssociationSetupResponseMsg.hpp
 *
 *  Created on: 10 May 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_SRC_MESSAGES_ASSOCIATIONSETUPRESPONSEMSG_HPP_
#define PROTO_SRC_MESSAGES_ASSOCIATIONSETUPRESPONSEMSG_HPP_

#include "Message.hpp"

namespace comuactiv {
namespace proto {
namespace messages {

class AssociationSetupResponseMsg: public Message {
public:
	AssociationSetupResponseMsg();
	virtual ~AssociationSetupResponseMsg();
};

} /* namespace messages */
} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_MESSAGES_ASSOCIATIONSETUPRESPONSEMSG_HPP_ */
