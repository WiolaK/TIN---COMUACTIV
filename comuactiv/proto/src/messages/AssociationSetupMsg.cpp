/*
 * AssociationSetupMsg.cpp
 *
 *  Created on: 10 May 2015
 *      Author: Jan Kumor
 */

#include "AssociationSetupMsg.hpp"

#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>

#include "../utils/Tokenizer.hpp"

using namespace comuactiv::proto::utils;

namespace comuactiv {
namespace proto {
namespace messages {

AssociationSetupMsg::AssociationSetupMsg(std::string lowPort)
: Message(defaultCode),
  lowPort_(lowPort) {
	std::stringstream ss;
	ss << lowPort_;
	this->setData(ss.str());
}

AssociationSetupMsg::AssociationSetupMsg(pRawMessage raw)
: Message(defaultCode) {
	memcpy(&header_, raw->array, sizeof(header_));
	//copying data
	int dataLength = header_.length_ - sizeof(header_);
	if( dataLength > 0 ) {
		data_.assign(raw->array+sizeof(header_), dataLength);
	}

	Tokenizer tokenizer('-');
	auto tokens = tokenizer(data_);

	if(tokens.size() != 1)
		std::cout << "BAD MESSAGE!" << std::endl;
	else
	{
		lowPort_ = tokens[0];
	}
}

AssociationSetupMsg::~AssociationSetupMsg() {
	// Do nothing
}

} /* namespace messages */
} /* namespace proto */
} /* namespace comuactiv */
