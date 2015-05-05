/*
 * Message.hpp
 *
 *  Created on: 4 May 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_SRC_MESSAGE_HPP_
#define PROTO_SRC_MESSAGE_HPP_

#include <iostream>
#include <stdint.h>

namespace comuactiv {
namespace proto {

class Message {
public:
	Message();
	virtual ~Message();

	friend std::ostream& operator<<(std::ostream &os, const Message& msg);

	friend std::istream& operator>>(std::istream &is, Message& msg);

private:
	uint16_t code_;
	uint16_t id_;
	std::string data_;
};

} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_MESSAGE_HPP_ */
