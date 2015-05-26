/*
 * RealChannel.hpp
 *
 *  Created on: 4 May 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_SRC_CHANNELS_REALCHANNEL_HPP_
#define PROTO_SRC_CHANNELS_REALCHANNEL_HPP_

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <utility>

#include "../messages/Message.hpp"
#include "../messages/RawMessage.hpp"
#include "../utils/Printer.hpp"
#include "../utils/ThreadBase.hpp"
#include "Channel.hpp"

namespace comuactiv {
namespace proto {
namespace channels {


class RealChannel: public utils::ThreadBase, public Channel {
public:
	RealChannel() : id_(0), log_(std::string("RealChannel#").append(std::to_string(id_))) {};
	RealChannel(int id, ChannelMode mode, Handlers handlers, std::string port, int sock): id_(id), log_(std::string("RealChannel#").append(std::to_string(id_))), mode_(mode), handlers_(handlers), port_(port), sock_(sock) {log_("created.");};
	virtual ~RealChannel();

	virtual bool start();

	virtual void* run();

	virtual std::string getPort() const {
		return port_;
	}

	virtual int getSock() const {
		return sock_;
	}

	virtual void writeMessage(messages::pRawMessage msg);
	virtual void writeAndHandleMessage(messages::pRawMessage msg);
	virtual messages::pMessage readMessage();
	void readAndHandleMessage();


	void handle(messages::pMessage msg);

private:
	int id_;
	utils::Printer log_;

	ChannelMode mode_;
	Handlers handlers_;

	std::string port_;
	int sock_;
	std::string host_;

	void startThread();
	messages::Message::MessageHeader readHeader();
	std::string readData(int length_);
	void initializeActive();
	void initializePassive();
	void workPassive();

};

/**
 * Sprytny wskaźnik na typ RealChannel.
 */
typedef std::shared_ptr<RealChannel> pRealChannel;

} /* namespace channels */
} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_CHANNELS_REALCHANNEL_HPP_ */
