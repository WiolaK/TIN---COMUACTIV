/*
 * ComuactivClientSlot.cpp
 *
 *  Created on: 4 May 2015
 *      Author: Jan Kumor
 */

#include <comuactiv/ComuactivClientSlot.hpp>
#include <pthread.h>
#include <unistd.h>
#include <algorithm>
#include <functional>
#include <memory>

#include "BlockingQueue.hpp"
#include "channels/Channel.hpp"
#include "channels/ProxyChannel.hpp"
#include "handlers/AssociationSetupResponseHandler.hpp"
#include "handlers/FlowTableEntryUpdateHandler.hpp"
#include "handlers/Handler.hpp"
#include "handlers/HeartbeatHandler.hpp"
#include "messages/AssociationSetupMsg.hpp"
#include "messages/Message.hpp"
#include "utils/Printer.hpp"
#include "utils/ThreadBase.hpp"

using namespace comuactiv::proto;
using namespace comuactiv::proto::messages;
using namespace comuactiv::proto::handlers;
using namespace comuactiv::proto::channels;
using namespace comuactiv::proto::utils;
using namespace comuactiv::proto::flowtable;

namespace comuactiv {
namespace proto {

class ComuactivClientSlot::ComuactivClientSlotImpl : public ThreadBase {
public:
	ComuactivClientSlotImpl();
	ComuactivClientSlotImpl(std::string host, std::string highPort, pFlowTable table);
	virtual ~ComuactivClientSlotImpl();

	virtual void* run();

	void insertCommand(pCommand command);

private:
	bool isStarted_;
	BlockingQueue blockingQueue_;
	Printer log_;
	pFlowTable table_;

	std::string host_;
	std::string highPort_;
	std::string mediumPort_;
	std::string lowPortActive_;

	//high is active at connection association then turns passive
	ProxyChannel high_;

	//medium is sending event notifiers to CE so it is active
	ProxyChannel medium_;

	//low must be asynchronous therefore active and passive channels
	ProxyChannel aLow_;
	ProxyChannel pLow_;

	void stageTwo(std::string mediumPort, std::string lowPort);
	void stageThree();
};

ComuactivClientSlot::ComuactivClientSlot(std::string host, std::string highPort, pFlowTable table)
: slot_( new ComuactivClientSlotImpl(host, highPort, table) ) {
	// do nothing
}

ComuactivClientSlot::ComuactivClientSlotImpl::ComuactivClientSlotImpl(std::string host, std::string highPort, pFlowTable table)
: isStarted_(true),
  log_(std::string("ComuactivClientSlot#")),
  table_(table),
  host_(host),
  highPort_(highPort) {
	log_("created.");
	pthread_create(&tid, nullptr, &execute, this);

}
/*
ComuactivSlot::ComuactivSlot(const ComuactivSlot& other)
    : slot_(new ComuactivSlot(*other.slot_)) {
    // do nothing
}*/

ComuactivClientSlot::ComuactivClientSlot(ComuactivClientSlot&& other)
: slot_(nullptr)
{
	std::swap(slot_, other.slot_);
}

ComuactivClientSlot& ComuactivClientSlot::operator=(const ComuactivClientSlot &other) {
	if(this != &other) {
		*slot_ = *(other.slot_);
	}
	return *this;
}

ComuactivClientSlot::~ComuactivClientSlot() {
	delete slot_;
}

ComuactivClientSlot::ComuactivClientSlotImpl::~ComuactivClientSlotImpl() {
	pthread_join(tid, nullptr);
	log_("thread joined.");
}

void ComuactivClientSlot::insertCommand(pCommand command) {
	slot_->insertCommand(command);
}

void ComuactivClientSlot::ComuactivClientSlotImpl::insertCommand(pCommand command) {
	blockingQueue_.push(command);
}

void ComuactivClientSlot::run() {
	slot_->run();
}

void* ComuactivClientSlot::ComuactivClientSlotImpl::run() {
	log_("Creating passive channels");
	pLow_ = ProxyChannel(Channel::PASSIVE);
	pLow_.registerHandler( Message::HEARTBEAT, pHandler(new HeartbeatHandler() ) );
	pLow_.start();

	log_(std::string("Initialising connection to: ").append(host_).append(std::string(":")).append(highPort_));

	high_ = ProxyChannel(Channel::ACTIVE);
	AssociationSetupResponseHandler::Callback aSRHcallback =
			std::bind(&ComuactivClientSlotImpl::stageTwo, this, std::placeholders::_1, std::placeholders::_2);
	high_.registerHandler(
			messages::Message::ASSOCIATION_SETUP_RESPONSE,
			pHandler( new AssociationSetupResponseHandler( aSRHcallback ) )
	);
	high_.setHost(host_);
	high_.setPort(highPort_);
	high_.start();

	//TODO: synchronizacja
	sleep(1);

	pMessage msg = pAssociationSetupMsg( new AssociationSetupMsg( pLow_.getPort() ) );
	high_.writeAndHandleMessage(msg->getRaw());
}

void ComuactivClientSlot::ComuactivClientSlotImpl::stageTwo(std::string mediumPort, std::string lowPort) {
	mediumPort_ = mediumPort;
	medium_ = ProxyChannel(Channel::ACTIVE);
	medium_.setHost(host_);
	medium_.setPort(mediumPort);
	medium_.start();

	lowPortActive_ = lowPort;
	aLow_ = ProxyChannel(Channel::ACTIVE);
	aLow_.setHost(host_);
	aLow_.setPort(lowPort);
	aLow_.start();

	high_.switchMode();
	high_.registerHandler(
			messages::Message::FLOW_TABLE_ENTRY_UPDATE,
			pHandler( new FlowTableEntryUpdateHandler(table_) )
	);
	high_.start();

	stageThree();
}

void ComuactivClientSlot::ComuactivClientSlotImpl::stageThree() {
	while(isStarted_) {
		pCommand command = blockingQueue_.pop();
		switch(command->code_) {
		/*case Command::SEND_FLOW_TABLE:
			executeCommand( std::static_pointer_cast<SendFlowTableCommand>(command) );
			break;*/

		default:
			break;
		}
	}
}

} /* namespace proto */
} /* namespace comuactiv */
