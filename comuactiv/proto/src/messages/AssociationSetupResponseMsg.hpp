/*
 * AssociationSetupResponseMsg.hpp
 *
 *  Created on: 10 May 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_SRC_MESSAGES_ASSOCIATIONSETUPRESPONSEMSG_HPP_
#define PROTO_SRC_MESSAGES_ASSOCIATIONSETUPRESPONSEMSG_HPP_

#include <memory>

#include "Message.hpp"
#include "RawMessage.hpp"

namespace comuactiv {
namespace proto {
namespace messages {

class AssociationSetupResponseMsg: public Message {
public:
	const static MsgCode defaultCode = ASSOCIATION_SETUP_RESPONSE;

	AssociationSetupResponseMsg(std::string mediumPort, std::string lowPort);

	AssociationSetupResponseMsg(pRawMessage raw);
	virtual ~AssociationSetupResponseMsg();

	static pMessage create(pRawMessage raw) {
		return pMessage(new AssociationSetupResponseMsg(raw));
	}

private:
	std::string mediumPort_;
	std::string lowPort_;
};

typedef std::shared_ptr<AssociationSetupResponseMsg> pAssociationSetupResponseMsg;

} /* namespace messages */
} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_MESSAGES_ASSOCIATIONSETUPRESPONSEMSG_HPP_ */
