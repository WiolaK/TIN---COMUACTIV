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
	std::cout << "Creating COMUACTIV ClientSlot" << std::endl;
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
	aHigh_ = pAChannel(new ActiveChannel(host_, highPort_));
	sleep(5);
	std::cout << "Input medium port: ";
	std::cin>>mediumPort_;
	aMedium_ = pAChannel(new ActiveChannel(host_, mediumPort_));
	std::cout << "Input low port: ";
	std::cin>>lowPort_;
	aMedium_ = pAChannel(new ActiveChannel(host_, lowPort_));
	sleep(10);
}

} /* namespace proto */
} /* namespace comuactiv */
