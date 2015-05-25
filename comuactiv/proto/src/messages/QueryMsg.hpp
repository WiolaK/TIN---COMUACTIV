/*
 * QueryMsg.hpp
 *
 *  Created on: 10 May 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_SRC_MESSAGES_QUERYMSG_HPP_
#define PROTO_SRC_MESSAGES_QUERYMSG_HPP_

#include "Message.hpp"

namespace comuactiv {
namespace proto {
namespace messages {

class QueryMsg: public Message {
public:
	const static MsgCode defaultCode = QUERY;

	QueryMsg();
	virtual ~QueryMsg();
};

} /* namespace messages */
} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_MESSAGES_QUERYMSG_HPP_ */
