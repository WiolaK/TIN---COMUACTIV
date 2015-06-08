/*
 * ComuactivServerSlot.hpp
 *
 *  Created on: 4 May 2015
 *      Author: Jan Kumor
 *
 */

#ifndef PROTO_SRC_COMUACTIVSERVERSLOT_HPP_
#define PROTO_SRC_COMUACTIVSERVERSLOT_HPP_

#include <memory>
#include <string>

#include "Command.hpp"

namespace comuactiv {
namespace proto {

class ComuactivServerSlot {
public:
	ComuactivServerSlot();
	ComuactivServerSlot(int sock, std::string host);
	//ComuactivServerSlot(const ComuactivServerSlot&) = delete;
	ComuactivServerSlot(ComuactivServerSlot&&);
	ComuactivServerSlot& operator=(const ComuactivServerSlot&);
	~ComuactivServerSlot();
	//Operations
	void insertCommand(pCommand command);
private:
	//not defined here
	class ComuactivServerSlotImpl;
	ComuactivServerSlotImpl* slot_;
};


typedef std::shared_ptr<ComuactivServerSlot> pComuactivServerSlot;
} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_COMUACTIVSERVERSLOT_HPP_ */
