/*
 * Message.hpp
 *
 *  Created on: 4 May 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_SRC_MESSAGES_MESSAGE_HPP_
#define PROTO_SRC_MESSAGES_MESSAGE_HPP_

#include <iostream>
#include <stdint.h>

#include <cereal/types/string.hpp>

namespace comuactiv {
namespace proto {
namespace messages {

/**
 * Base class for COMUACTIVE protocol messages
 */
class Message {
public:
	enum MsgCode : uint8_t {
		ASSOCIATION_SETUP = 72,
				ASSOCIATION_SETUP_RESPONSE,
				ASSOCIATION_TEARDOWN,
				CONFIGURATION,
				CONFIGURATION_RESPONSE,
				QUERY,
				QUERY_RESPONSE,
				FLOW_TABLE_ENTRY_UPDATE,
				EVENT_NOTIFICATION,
				PACKET_REDIRECT,
				HEARTBEAT
	};

	Message();
	virtual ~Message();

	template<class Archive>	void serialize(Archive& ar)
	{
		ar( prefix_, code_, length_, id_, data_ );
	}

//protected:
	Message( MsgCode code);
	std::string prefix_;
	uint8_t code_;
	uint32_t length_;
	uint32_t id_;
	std::string data_;

};

} /* namespace messages */
} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_MESSAGES_MESSAGE_HPP_ */
