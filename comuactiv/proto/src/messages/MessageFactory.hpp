/*
 * MessageFactory.hpp
 *
 *  Created on: 10 May 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_SRC_MESSAGEFACTORY_HPP_
#define PROTO_SRC_MESSAGEFACTORY_HPP_

#include <map>
#include <memory>

#include "Message.hpp"

namespace comuactiv {
namespace proto {
namespace messages {

/**
 * Abstract factory of COMUACTIV protocol messages. Is a singleton class.
 */
class MessageFactory {
public:
	/**
	 * returns instance of singleton MessageFactory.
	 */
	static MessageFactory& getInstance();


	typedef	Message* (*CreateMessageFun)();
	/**
	 * register new type in MessageFactory.
	 */
	bool registerMessage(Message::MsgCode code, CreateMessageFun fun);

	/**
	 * creates specific message basing on message code
	 */
	pMessage create(Message::MsgCode code);

	void initialize();

private:
	// singleton pattern
	MessageFactory();
	virtual ~MessageFactory();
	MessageFactory(const MessageFactory&) = delete;
	MessageFactory& operator=(const MessageFactory&) = delete;

	typedef	std::map<int, CreateMessageFun> Callbacks;
	Callbacks callbacks_;
};

} /* namespace messages */
} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_MESSAGEFACTORY_HPP_ */
