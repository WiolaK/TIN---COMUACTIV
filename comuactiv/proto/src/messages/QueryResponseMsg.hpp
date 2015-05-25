/*
 * QueryResponseMsg.hpp
 *
 *  Created on: 10 May 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_SRC_MESSAGES_QUERYRESPONSEMSG_HPP_
#define PROTO_SRC_MESSAGES_QUERYRESPONSEMSG_HPP_

#include "Message.hpp"

namespace comuactiv {
namespace proto {
namespace messages {

class QueryResponseMsg: public Message {
public:
	const static MsgCode defaultCode = QUERY_RESPONSE;

	QueryResponseMsg();
	virtual ~QueryResponseMsg();
};

} /* namespace messages */
} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_MESSAGES_QUERYRESPONSEMSG_HPP_ */
