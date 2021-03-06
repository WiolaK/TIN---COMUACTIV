/*
 * ComuactivServerSlot.cpp
 *
 *  Created on: 4 May 2015
 *      Author: Jan Kumor
 */

#include <comuactiv/ComuactivServerSlot.hpp>
#include <comuactiv/SendFlowTableCommand.hpp>
#include <pthread.h>
#include <unistd.h>
#include <algorithm>
#include <functional>

#include "BlockingQueue.hpp"
#include "channels/Channel.hpp"
#include "channels/ProxyChannel.hpp"
#include "handlers/AssociationSetupHandler.hpp"
#include "handlers/EventNotificationHandler.hpp"
#include "handlers/Handler.hpp"
#include "handlers/HeartbeatHandler.hpp"
#include "messages/AssociationSetupResponseMsg.hpp"
#include "messages/FlowTableEntryUpdateMsg.hpp"
#include "messages/Message.hpp"
#include "utils/Printer.hpp"
#include "utils/ThreadBase.hpp"


using namespace comuactiv::proto;
using namespace comuactiv::proto::messages;
using namespace comuactiv::proto::handlers;
using namespace comuactiv::proto::channels;
using namespace comuactiv::proto::utils;

namespace comuactiv {
namespace proto {

class ComuactivServerSlot::ComuactivServerSlotImpl
		: public ThreadBase,
		  public std::enable_shared_from_this<ComuactivServerSlotImpl> {
public:
	static int counter_;

	ComuactivServerSlotImpl();
	ComuactivServerSlotImpl(int sock, std::string host);
	virtual ~ComuactivServerSlotImpl();

	void insertCommand(pCommand command);

	virtual void* run();

	void stageTwo(std::string lowPort);
	void stageThree();
private:
	int id_;
	Printer log_;
	bool isStarted_;
	BlockingQueue blockingQueue_;

	int sock_;

	std::string host_;
	std::string highPort_;
	std::string mediumPort_;
	std::string lowPort_;

	//high is initialized as passive then after association turns into active
	ProxyChannel high_;

	//medium is always listening for events from FE therefore passive
	ProxyChannel medium_;

	//low must be asynchronous therefore active and passive
	ProxyChannel pLow_;
	ProxyChannel aLow_;

	void executeCommand(pSendFlowTableCommand command);
};

int ComuactivServerSlot::ComuactivServerSlotImpl::counter_ = 0;

ComuactivServerSlot::ComuactivServerSlot()
: slot_(new ComuactivServerSlotImpl()) {
	// do nothing
}

ComuactivServerSlot::ComuactivServerSlot(int sock, std::string host)
: slot_(new ComuactivServerSlotImpl(sock, host)) {
	// do nothing
}

ComuactivServerSlot::ComuactivServerSlotImpl::ComuactivServerSlotImpl()
: id_(++counter_) {

}

ComuactivServerSlot::ComuactivServerSlotImpl::ComuactivServerSlotImpl(int sock, std::string host)
: id_(++counter_),
  log_(std::string("ComuactivServerSlot#").append(std::to_string(id_))),
  isStarted_(true),
  sock_(sock),
  host_(host) {
	log_("created.");
	pthread_create(&tid, nullptr, &execute, this);
}

/*

ComuactivSlot::ComuactivSlot(const ComuactivSlot& other)
    : slot_(new ComuactivSlot(*other.slot_)) {
    // do nothing
}*/

ComuactivServerSlot::ComuactivServerSlot(ComuactivServerSlot&& other)
: slot_(0)
{
	std::swap(slot_, other.slot_);
}

ComuactivServerSlot& ComuactivServerSlot::operator=(const ComuactivServerSlot &other) {
	if(this != &other) {
		*slot_ = *(other.slot_);
	}
	return *this;
}


ComuactivServerSlot::~ComuactivServerSlot() {
	delete slot_;
}

ComuactivServerSlot::ComuactivServerSlotImpl::~ComuactivServerSlotImpl() {
	log_("Joining thread.");
	pthread_join(tid, nullptr);
}

void ComuactivServerSlot::insertCommand(pCommand command) {
	slot_->insertCommand(command);
}

void ComuactivServerSlot::ComuactivServerSlotImpl::insertCommand(pCommand command) {
	blockingQueue_.push(command);
}

void* ComuactivServerSlot::ComuactivServerSlotImpl::run() {
	log_("STARTING PASSIVE CHANNELS");
	medium_ = ProxyChannel(Channel::PASSIVE);
	medium_.registerHandler(Message::EVENT_NOTIFICATION, pHandler(new EventNotificationHandler() ) );
	medium_.start();

	pLow_ = ProxyChannel(Channel::PASSIVE);
	pLow_.registerHandler(Message::HEARTBEAT, pHandler(new HeartbeatHandler() ) );
	pLow_.start();
	//TODO: synchronizacja
	sleep(2);
	high_ = ProxyChannel(Channel::PASSIVE);
	AssociationSetupHandler::Callback aSHcallback = std::bind(&ComuactivServerSlotImpl::stageTwo, this, std::placeholders::_1);
	high_.registerHandler(Message::ASSOCIATION_SETUP, pHandler(new AssociationSetupHandler(aSHcallback) ) );
	high_.setSock(sock_);
	high_.start();

	return nullptr;
}

void ComuactivServerSlot::ComuactivServerSlotImpl::stageTwo(std::string lowPort) {
	mediumPort_ = medium_.getPort();
	lowPort_ = pLow_.getPort();

	aLow_ = ProxyChannel(Channel::ACTIVE);
	aLow_.setHost(high_.getHost());
	aLow_.setPort(lowPort);
	aLow_.start();

	pMessage response = pAssociationSetupResponseMsg( new AssociationSetupResponseMsg( lowPort_, mediumPort_ ) );
	high_.writeMessage(response->getRaw());

	high_.switchMode();
	high_.start();
	stageThree();
}

void ComuactivServerSlot::ComuactivServerSlotImpl::stageThree() {
	while(isStarted_) {
		pCommand command = blockingQueue_.pop();
		switch(command->code_) {
		case Command::SEND_FLOW_TABLE:
			executeCommand( std::static_pointer_cast<SendFlowTableCommand>(command) );
			break;

		default:
			break;
		}
	}
}

void ComuactivServerSlot::ComuactivServerSlotImpl::executeCommand(pSendFlowTableCommand command) {
	FlowTableEntryUpdateMsg message(command->getTableString());
	high_.writeMessage(message.getRaw());
}

} /* namespace proto */
} /* namespace comuactiv */

