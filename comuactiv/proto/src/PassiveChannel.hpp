/*
 * PassiveChannel.hpp
 *
 *  Created on: 4 May 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_SRC_PASSIVECHANNEL_HPP_
#define PROTO_SRC_PASSIVECHANNEL_HPP_

#include "ThreadBase.hpp"

namespace comuactiv {
namespace proto {

class PassiveChannel: public ThreadBase {
public:
	static int counter_;

	PassiveChannel();
	PassiveChannel(int sock);
	virtual ~PassiveChannel();


	virtual void* run();
	int getSock() { return sock_;}

private:
	void initialize();
	void work();

	int id_;
	int sock_;
};

} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_CHANNEL_HPP_ */
