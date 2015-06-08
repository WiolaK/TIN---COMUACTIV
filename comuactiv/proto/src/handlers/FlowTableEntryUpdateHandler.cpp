/*
 * FlowTableEntryUpdateHandler.cpp
 *
 *  Created on: 25 May 2015
 *      Author: Jan Kumor
 */

#include "FlowTableEntryUpdateHandler.hpp"

#include <memory>

#include "../../include/comuactiv/FlowTable.hpp"
#include "../messages/FlowTableEntryUpdateMsg.hpp"
#include "../utils/Printer.hpp"

using namespace comuactiv::proto::messages;
using namespace comuactiv::proto::flowtable;

namespace comuactiv {
namespace proto {
namespace handlers {

FlowTableEntryUpdateHandler::FlowTableEntryUpdateHandler(pFlowTable table)
: table_(table) {
	// TODO Auto-generated constructor stub
}

FlowTableEntryUpdateHandler::~FlowTableEntryUpdateHandler() {
	// TODO Auto-generated destructor stub
}

void FlowTableEntryUpdateHandler::operator ()(pMessage msg) {
	utils::Printer printer("FlowTableEntryUpdateHandler");
	printer("executed");
	pFlowTableEntryUpdateMsg fTEUMsg = std::static_pointer_cast<FlowTableEntryUpdateMsg>(msg);
	table_->parseTable(fTEUMsg->getTableString());
	table_->checkTable();
//	callback_();
}

} /* namespace handlers */
} /* namespace proto */
} /* namespace comuactiv */
