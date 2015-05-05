/*
 * ComuactivServerSlot.hpp
 *
 *  Created on: 4 May 2015
 *      Author: Jan Kumor
 *
 */

#ifndef PROTO_SRC_COMUACTIVSERVERSLOT_HPP_
#define PROTO_SRC_COMUACTIVSERVERSLOT_HPP_

namespace comuactiv {
namespace proto {

class ComuactivServerSlot {
public:
	ComuactivServerSlot();
	ComuactivServerSlot(int sock_);
//	ComuactivSlot(const ComuactivSlot&);           	// Copy constructor
	ComuactivServerSlot(ComuactivServerSlot&&);
	ComuactivServerSlot& operator=(const ComuactivServerSlot&);
	~ComuactivServerSlot();
	//Operations
	void run();
private:
	//not defined here
	class ComuactivServerSlotImpl;
	ComuactivServerSlotImpl* slot_;
};

} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_COMUACTIVSERVERSLOT_HPP_ */
