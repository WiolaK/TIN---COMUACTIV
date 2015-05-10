/*
 * MessageFactory.cpp
 *
 *  Created on: 10 May 2015
 *      Author: Jan Kumor
 */

#include <stdexcept>

#include "MessageFactory.hpp"

namespace comuactiv {
namespace proto {

MessageFactory::MessageFactory() {

}

MessageFactory& MessageFactory::MessageFactory::getInstance() {
	static MessageFactory instance;
	return instance;
}

MessageFactory::~MessageFactory() {
}

bool MessageFactory::RegisterMessage( int code, CreateMessageFun fun) {
	return ( callbacks_.insert( std::pair<int, CreateMessageFun>(code, fun) ) ).second;
}

messages::Message* MessageFactory::create( int code) {
	Callbacks::const_iterator iter = callbacks_.find(code);
	if(iter == callbacks_.end() ) {
		//throw std::runtime_error( std::string("Wrong message code!") ) ;
		return nullptr;
	} else {
		return (iter->second)();
	}
}

} /* namespace proto */
} /* namespace comuactiv */
