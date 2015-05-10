/*
 * ConfigurationMsg.h
 *
 *  Created on: 10 May 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_SRC_MESSAGES_CONFIGURATIONMSG_HPP_
#define PROTO_SRC_MESSAGES_CONFIGURATIONMSG_HPP_

#include "Message.hpp"

namespace comuactiv {
namespace proto {
namespace messages {

class ConfigurationMsg: public Message {
public:
	ConfigurationMsg();
	virtual ~ConfigurationMsg();
};

} /* namespace messages */
} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_MESSAGES_CONFIGURATIONMSG_HPP_ */
