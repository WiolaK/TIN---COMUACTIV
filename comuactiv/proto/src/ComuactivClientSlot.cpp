/*
 * ComuactivClientSlot.cpp
 *
 *  Created on: 4 May 2015
 *      Author: Jan Kumor
 */

#include <algorithm>

#include <stdio.h>

#include <cstring>
#include <iostream>
#include <string>

#include <ComuactivClientSlot.hpp>

#include "comuactiv_utils.hpp"
#include "Channel.hpp"
#include "ActiveChannel.hpp"
#include "PassiveChannel.hpp"

#define DATA "Some msg"

#define LOG(x) std::cout << "COMUACTIVE ClientSlot: " << x << std::endl

using namespace comuactiv::proto;

namespace comuactiv {
namespace proto {

class ComuactivClientSlot::ComuactivClientSlotImpl {
public:
	ComuactivClientSlotImpl(std::string host, std::string highPort);
	void run();

private:
	std::string host_;
	std::string highPort_;
	std::string mediumPort_;
	std::string lowPort_;
	pAChannel aHigh_;
	pAChannel aMedium_;
	pAChannel aLow_;
	pPChannel pHigh_;
	pPChannel pMedium_;
	pPChannel pLow_;
};

ComuactivClientSlot::ComuactivClientSlot(std::string host, std::string highPort)
: slot_( new ComuactivClientSlotImpl(host, highPort) ) {
	// do nothing
}

ComuactivClientSlot::ComuactivClientSlotImpl::ComuactivClientSlotImpl(std::string host, std::string highPort)
: host_(host),
  highPort_(highPort),
  pHigh_(new PassiveChannel()),
  pMedium_(new PassiveChannel()),
  pLow_(new PassiveChannel()) {
	LOG("created.");
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

void ComuactivClientSlot::run() {
	slot_->run();
}

void ComuactivClientSlot::ComuactivClientSlotImpl::run() {
	LOG("Initialising connection to: " << host_ << ":" << highPort_);
	aHigh_ = pAChannel(new ActiveChannel(host_, highPort_));
	sleep(1);
	LOG("Input medium port: ");
	std::cin>>mediumPort_;
	LOG("Initialising connection to: " << host_ << ":" << mediumPort_);
	aMedium_ = pAChannel(new ActiveChannel(host_, mediumPort_));
	LOG("Input low port: ");
	std::cin>>lowPort_;
	LOG("Initialising connection to: " << host_ << ":" << lowPort_);
	aLow_ = pAChannel(new ActiveChannel(host_, lowPort_));
	while(true) {
		LOG("Writing to high");
		aHigh_->writeData(DATA);
		sleep(1);
		LOG("Writing to medium");
		aMedium_->writeData(DATA);
		sleep(1);
		LOG("Writing to low");
		aLow_->writeData(DATA);
		sleep(1);
	}
}

} /* namespace proto */
} /* namespace comuactiv */
