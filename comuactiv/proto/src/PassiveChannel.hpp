/*
 * PassiveChannel.hpp
 *
 *  Created on: 4 May 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_SRC_PASSIVECHANNEL_HPP_
#define PROTO_SRC_PASSIVECHANNEL_HPP_

#include <memory>
#include <string>

#include "ActiveChannel.hpp"
#include "ThreadBase.hpp"

namespace comuactiv {
namespace proto {

class PassiveChannel: public ThreadBase {
public:
	static int counter_;

	PassiveChannel();
	PassiveChannel(int arg, bool isSock);
	PassiveChannel(pAChannel active);
	virtual ~PassiveChannel();

	virtual void* run();
	int getSock() { return sock_;}

private:
	void initialize();
	void work();
	void startThread();

	int id_;
	int sock_;
	int port_;
};

/**
 * Sprytny wskaźnik (std::shared_ptr) na klasę PassiveChannel
 */
typedef std::shared_ptr<PassiveChannel> pPChannel;

} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_CHANNEL_HPP_ */
