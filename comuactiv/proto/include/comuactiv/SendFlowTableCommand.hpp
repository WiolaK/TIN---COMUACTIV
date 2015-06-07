/*
 * SendFlowTableCommand.hpp
 *
 *  Created on: 7 Jun 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_INCLUDE_COMUACTIV_SENDFLOWTABLECOMMAND_HPP_
#define PROTO_INCLUDE_COMUACTIV_SENDFLOWTABLECOMMAND_HPP_

#include <string>

#include "Command.hpp"

namespace comuactiv {
namespace proto {

class SendFlowTableCommand: public Command {
public:
	SendFlowTableCommand(std::string tableString) : Command(CommandCode::SEND_FLOW_TABLE), tableString_(tableString) {};
	virtual ~SendFlowTableCommand() {};
	std::string getTableString() { return tableString_; }

private:
	std::string tableString_;
};

typedef std::shared_ptr<SendFlowTableCommand> pSendFlowTableCommand;

} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_INCLUDE_COMUACTIV_SENDFLOWTABLECOMMAND_HPP_ */
