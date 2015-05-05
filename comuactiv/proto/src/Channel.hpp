/*
 * Channel.hpp
 *
 *  Created on: 4 May 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_SRC_CHANNEL_HPP_
#define PROTO_SRC_CHANNEL_HPP_

#include "ThreadBase.hpp"

namespace comuactiv {
namespace proto {

class Channel: public ThreadBase {
public:
	static int counter_;

	enum ChannelMode {
		PASSIVE,
		ACTIVE
	};

	Channel() {};
	Channel( int sock, ChannelMode mode);
	virtual ~Channel();


	virtual void* run();

private:
	int id_;
	int sock_;
	ChannelMode mode_;
};

} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_CHANNEL_HPP_ */
