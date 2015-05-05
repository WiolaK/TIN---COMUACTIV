/*
 * Message.cpp
 *
 *  Created on: 4 May 2015
 *      Author: Jan Kumor
 */

#include "Message.hpp"
#include <cereal/cereal.hpp>
namespace comuactiv {
namespace proto {

Message::Message() {
	// TODO Auto-generated constructor stub
}

Message::~Message() {
	// TODO Auto-generated destructor stub
}

std::ostream& operator<<(std::ostream &os, const Message& msg) {
	os << "COMUACTIV" << msg.code_ << msg.id_ << msg.data_;
	return os;
}

std::istream& operator>>(std::istream &is, Message& msg) {
	is >> msg.code_ >> msg.id_ >> msg.data_;
	return is;
}

} /* namespace proto */
} /* namespace comuactiv */
