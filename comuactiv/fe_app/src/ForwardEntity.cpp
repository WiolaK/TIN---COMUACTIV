/*
 * ForwardEntity.cpp
 *
 *  Created on: 3 May 2015
 *      Author: Jan Kumor
 */

#include "ForwardEntity.hpp"

#include "../../proto/include/comuactiv/ComuactivClientSlot.hpp"
#include "../../proto/include/comuactiv/FlowTable.hpp"
#include <iostream>
#include <string>

#include "UDPStreamer.hpp"


using namespace comuactiv::fe_app;
using namespace comuactiv::proto;
using namespace comuactiv::proto::flowtable;

namespace comuactiv {
namespace fe_app {

ForwardEntity::ForwardEntity() {

}

ForwardEntity& ForwardEntity::ForwardEntity::getInstance() {
	static ForwardEntity instance;
	return instance;
}

void ForwardEntity::start(std::string host, std::string highPort, std::string streamerPort) {
	std::cout << "FE Started" << std::endl;
	pFlowTable table(new FlowTable);
//	std::unique_ptr<ComuactivClientSlot> slot(new ComuactivClientSlot(host, highPort, table));
	ComuactivClientSlot slot(host, highPort, table);
	UDPStreamer streamer(streamerPort, table);
}

} /* namespace fe_app */
} /* namespace comuactiv */
