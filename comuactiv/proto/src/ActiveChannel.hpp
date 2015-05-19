/*
 * ActiveChannel.hpp
 *
 *  Created on: 4 May 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_SRC_ACTIVECHANNEL_HPP_
#define PROTO_SRC_ACTIVECHANNEL_HPP_

#include <string>

#include "ThreadBase.hpp"

namespace comuactiv {
namespace proto {

class ActiveChannel: public ThreadBase {
public:
	static int counter_;

	ActiveChannel(std::string host, std::string port);
	virtual ~ActiveChannel();


	virtual void* run();
	void writeData(char* data, int size);

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

} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_CHANNEL_HPP_ */
