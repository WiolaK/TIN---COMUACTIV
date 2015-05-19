/*
 * ActiveChannel.hpp
 *
 *  Created on: 4 May 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_SRC_ACTIVECHANNEL_HPP_
#define PROTO_SRC_ACTIVECHANNEL_HPP_

#include <string>

#include "messages/RawMessage.hpp"
#include "ThreadBase.hpp"

namespace comuactiv {
namespace proto {

class ActiveChannel: public ThreadBase {
public:
	static int counter_;

	ActiveChannel(std::string host, std::string port);
	virtual ~ActiveChannel();


	virtual void* run();
	void writeMessage(messages::pRawMessage msg);

	void listenResponse();

	int getSock() const {
		return sock_;
	}

private:
	void initialize();

	int id_;
	int sock_;
	std::string host_;
	std::string port_;
};

/**
 * Sprytny wskaźnik (std::shared_ptr) na strukturę ActiveChannel
 */
typedef std::shared_ptr<ActiveChannel> pAChannel;

} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_CHANNEL_HPP_ */
