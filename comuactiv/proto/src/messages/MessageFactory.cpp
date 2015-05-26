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
#include "RawMessage.hpp"

namespace comuactiv {
namespace proto {
namespace messages {

bool MessageFactory::isInitialized_ = false;

MessageFactory::MessageFactory() {
	//Do nothing
}

MessageFactory& MessageFactory::MessageFactory::getInstance() {
	static MessageFactory instance;
	if( !isInitialized_) {
		instance.initialize();
	}
	return instance;
}

/*struct RegisterMessage {
	template<typename T> void operator()(T) {
		MessageFactory::getInstance().registerMessage(T::defaultCode, T::create);
	}
};*/

void MessageFactory::initialize() {
//	typedef boost::mpl::vector<AssociationSetupMsg, AssociationSetupResponseMsg, HeartbeatMsg> MessageTypes;
//	boost::mpl::for_each< MessageTypes >( RegisterMessage() );
	this->registerMessage(AssociationSetupMsg::defaultCode, AssociationSetupMsg::create);
	this->registerMessage(AssociationSetupResponseMsg::defaultCode, AssociationSetupResponseMsg::create);
	this->registerMessage(HeartbeatMsg::defaultCode, HeartbeatMsg::create);
	isInitialized_ = true;
}

MessageFactory::~MessageFactory() {
}

bool MessageFactory::registerMessage(Message::MsgCode code, CreateFun fun) {
	return ( callbacks_.insert( std::pair<Message::MsgCode, CreateFun>(code, fun) ) ).second;
}

pMessage MessageFactory::create(Message::MsgCode code, pRawMessage raw) {
	Callbacks::const_iterator iter = callbacks_.find(code);
	if(iter == callbacks_.end() ) {
		//throw std::runtime_error( std::string("Wrong message code!") ) ;
		return nullptr;
	} else {
		return pMessage((iter->second)(raw));
	}
}

} /* namespace messages */
} /* namespace proto */
} /* namespace comuactiv */
