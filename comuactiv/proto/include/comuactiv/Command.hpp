/*
 * Command.hpp
 *
 *  Created on: 7 Jun 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_INCLUDE_COMUACTIV_COMMAND_HPP_
#define PROTO_INCLUDE_COMUACTIV_COMMAND_HPP_

#include <memory>

namespace comuactiv {
namespace proto {

class Command {
public:
	enum CommandCode {
		SEND_FLOW_TABLE = 0
	};
	Command(CommandCode code) : code_(code) {};
	virtual ~Command() {};

	const CommandCode code_;

};

typedef std::shared_ptr<Command> pCommand;

} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_INCLUDE_COMUACTIV_COMMAND_HPP_ */
