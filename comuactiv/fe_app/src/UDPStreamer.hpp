/*
 * UDPStreamer.hpp
 *
 *  Created on: 8 Jun 2015
 *      Author: Wioletta Klimczak
 */

#ifndef FE_APP_SRC_UDPSTREAMER_HPP_
#define FE_APP_SRC_UDPSTREAMER_HPP_

#include <string>

#include "../../proto/include/comuactiv/FlowTable.hpp"
#include "../../proto/src/utils/Printer.hpp"
#include "../../proto/src/utils/ThreadBase.hpp"

//TODO: [JKU] te nagłówki powinny trafić do oddzielnej comuactiv utils
namespace comuactiv {
namespace fe_app {

class UDPStreamer : public proto::utils::ThreadBase {
public:
	UDPStreamer(std::string port, proto::flowtable::pFlowTable table);
	virtual ~UDPStreamer();

	virtual void* run();

private:
	proto::utils::Printer log_;
	std::string port_;
	proto::flowtable::pFlowTable table_;
};

} /* namespace fe_app */
} /* namespace comuactiv */

#endif /* FE_APP_SRC_UDPSTREAMER_HPP_ */
