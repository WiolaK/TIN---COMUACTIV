/*
 * AssociationTeardownMsg.hpp
 *
 *  Created on: 10 May 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_SRC_MESSAGES_ASSOCIATIONTEARDOWNMSG_HPP_
#define PROTO_SRC_MESSAGES_ASSOCIATIONTEARDOWNMSG_HPP_

#include "Message.hpp"

namespace comuactiv {
namespace proto {
namespace messages {

class AssociationTeardownMsg: public Message {
public:
	AssociationTeardownMsg();
	virtual ~AssociationTeardownMsg();
};

} /* namespace messages */
} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_MESSAGES_ASSOCIATIONTEARDOWNMSG_HPP_ */
