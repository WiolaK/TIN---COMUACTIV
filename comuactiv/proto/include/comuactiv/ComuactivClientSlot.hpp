/*
 * ComuactivClientSlot.hpp
 *
 *  Created on: 4 May 2015
 *      Author: Jan Kumor
 *
 */

#ifndef PROTO_SRC_COMUACTIVCLIENTSLOT_HPP_
#define PROTO_SRC_COMUACTIVCLIENTSLOT_HPP_

#include <string>

namespace comuactiv {
namespace proto {

class ComuactivClientSlot {
public:
	ComuactivClientSlot(std::string host, std::string highPort);
//	ComuactivSlot(const ComuactivSlot&);           	// Copy constructor
	ComuactivClientSlot(ComuactivClientSlot&&);
	ComuactivClientSlot& operator=(const ComuactivClientSlot&);
	~ComuactivClientSlot();
	//Operations
	void run();
private:
	//not defined here
	class ComuactivClientSlotImpl;
	ComuactivClientSlotImpl* slot_;
};

} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_COMUACTIVCLIENTSLOT_HPP_ */
