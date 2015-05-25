/*
 * ConfigurationResponseMsg.hpp
 *
 *  Created on: 10 May 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_SRC_MESSAGES_CONFIGURATIONRESPONSEMSG_HPP_
#define PROTO_SRC_MESSAGES_CONFIGURATIONRESPONSEMSG_HPP_

#include "Message.hpp"

namespace comuactiv {
namespace proto {
namespace messages {

class ConfigurationResponseMsg: public Message {
public:
	const static MsgCode defaultCode = CONFIGURATION_RESPONSE;

	ConfigurationResponseMsg();
	virtual ~ConfigurationResponseMsg();
};

} /* namespace messages */
} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_MESSAGES_CONFIGURATIONRESPONSEMSG_HPP_ */
