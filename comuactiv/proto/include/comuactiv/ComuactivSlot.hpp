/*
 * ComuactivSlot.hpp
 *
 *  Created on: 7 Jun 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_INCLUDE_COMUACTIV_COMUACTIVSLOT_HPP_
#define PROTO_INCLUDE_COMUACTIV_COMUACTIVSLOT_HPP_

namespace comuactiv {
namespace proto {

class ComuactivSlot {
public:
	ComuactivSlot();
	virtual ~ComuactivSlot();
};

typedef std::shared_ptr<ComuactivSlot> pComuactivSlot;
} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_INCLUDE_COMUACTIV_COMUACTIVSLOT_HPP_ */
