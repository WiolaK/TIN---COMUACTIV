/*
 * ComuactivServerSlot.cpp
 *
 *  Created on: 4 May 2015
 *      Author: Jan Kumor
 */

#include <comuactiv/ComuactivServerSlot.hpp>
#include <pthread.h>
#include <unistd.h>
#include <algorithm>
#include <memory>

#include "channels/Channel.hpp"
#include "channels/ProxyChannel.hpp"
#include "handlers/AssociationSetupHandler.hpp"
#include "handlers/EventNotificationHandler.hpp"
#include "handlers/Handler.hpp"
#include "handlers/HeartbeatHandler.hpp"
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

class ComuactivServerSlot::ComuactivServerSlotImpl : public ThreadBase {
public:
	static int counter_;

	ComuactivServerSlotImpl();
	ComuactivServerSlotImpl(int sock, std::string mediumPort, std::string lowPort);
	virtual ~ComuactivServerSlotImpl();

	virtual void* run();

private:
	int id_;
	Printer log_;

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
};

int ComuactivServerSlot::ComuactivServerSlotImpl::counter_ = 0;

ComuactivServerSlot::ComuactivServerSlot()
: slot_(new ComuactivServerSlotImpl()) {
	// do nothing
}

ComuactivServerSlot::ComuactivServerSlot(int sock, std::string mediumPort, std::string lowPort)
: slot_(new ComuactivServerSlotImpl(sock, mediumPort, lowPort)) {
	// do nothing
}

ComuactivServerSlot::ComuactivServerSlotImpl::ComuactivServerSlotImpl()
: id_(++counter_) {

}

ComuactivServerSlot::ComuactivServerSlotImpl::ComuactivServerSlotImpl(int sock, std::string mediumPort, std::string lowPort)
: id_(++counter_),
  log_(std::string("ComuactivServerSlot#").append(std::to_string(id_))),
  sock_(sock),
  mediumPort_(mediumPort),
  lowPort_(lowPort) {
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
	log_("JOINING THREAD");
	pthread_join(tid, nullptr);
}

void* ComuactivServerSlot::ComuactivServerSlotImpl::run() {
	log_("STARTING PASSIVE CHANNELS");
	high_ = ProxyChannel(Channel::PASSIVE);
	high_.registerHandler(Message::ASSOCIATION_SETUP, pHandler(new AssociationSetupHandler(high_) ) );
	high_.setSock(sock_);
	high_.start();

	medium_ = ProxyChannel(Channel::PASSIVE);
	medium_.registerHandler(Message::EVENT_NOTIFICATION, pHandler(new EventNotificationHandler() ) );
	medium_.start();

	pLow_ = ProxyChannel(Channel::PASSIVE);
	pLow_.registerHandler(Message::HEARTBEAT, pHandler(new HeartbeatHandler() ) );
	pLow_.start();
	//TODO: synchronizacja
	sleep(1);

	mediumPort_ = medium_.getPort();
	log_(std::string("Assigned medium port:").append(mediumPort_));

	lowPort_ = pLow_.getPort();
	log_(std::string("Assigned passive low port:").append(lowPort_));


	return nullptr;
}

} /* namespace proto */
} /* namespace comuactiv */

