/*
 * MessageFactory.cpp
 *
 *  Created on: 10 May 2015
 *      Author: Jan Kumor
 */

#include "MessageFactory.hpp"

#include <boost/mpl/vector.hpp>
#include <boost/mpl/for_each.hpp>
#include <utility>

#include "AssociationSetupMsg.hpp"
#include "AssociationSetupResponseMsg.hpp"
#include "HeartbeatMsg.hpp"

namespace comuactiv {
namespace proto {
namespace messages {

MessageFactory::MessageFactory() {

}

MessageFactory& MessageFactory::MessageFactory::getInstance() {
	static MessageFactory instance;
	return instance;
}

struct RegisterMessage {
	template<typename T> void operator()(T) {
		MessageFactory::getInstance().registerMessage(T::defaultCode, T::create);
	}
};

void MessageFactory::initialize() {
	typedef boost::mpl::vector<AssociationSetupMsg, AssociationSetupResponseMsg, HeartbeatMsg> MessageTypes;
	boost::mpl::for_each< MessageTypes >( RegisterMessage() );
}

MessageFactory::~MessageFactory() {
}

bool MessageFactory::registerMessage(Message::MsgCode code, CreateMessageFun fun) {
	return ( callbacks_.insert( std::pair<int, CreateMessageFun>(code, fun) ) ).second;
}

pMessage MessageFactory::create(Message::MsgCode code) {
	Callbacks::const_iterator iter = callbacks_.find(code);
	if(iter == callbacks_.end() ) {
		//throw std::runtime_error( std::string("Wrong message code!") ) ;
		return nullptr;
	} else {
		return pMessage((iter->second)());
	}
}

} /* namespace messages */
} /* namespace proto */
} /* namespace comuactiv */
