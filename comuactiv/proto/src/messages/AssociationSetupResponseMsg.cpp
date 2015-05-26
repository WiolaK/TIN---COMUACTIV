/*
 * AssociationSetupResponseMsg.cpp
 *
 *  Created on: 10 May 2015
 *      Author: Jan Kumor
 */

#include "AssociationSetupResponseMsg.hpp"

#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../utils/Tokenizer.hpp"

using namespace comuactiv::proto::utils;

namespace comuactiv {
namespace proto {
namespace messages {

AssociationSetupResponseMsg::AssociationSetupResponseMsg(std::string mediumPort, std::string lowPort)
: Message(defaultCode),
  mediumPort_(mediumPort),
  lowPort_(lowPort) {
	std::stringstream ss;
	ss << mediumPort_ << "-" << lowPort_;
	this->setData(ss.str());
}

AssociationSetupResponseMsg::AssociationSetupResponseMsg(pRawMessage raw)
: Message(defaultCode) {
	memcpy(&header_, raw->array, sizeof(header_));
	//copying data
	int dataLength = header_.length_ - sizeof(header_);
	if( dataLength > 0 ) {
		data_.assign(raw->array+sizeof(header_), dataLength);
	}

	std::cout << "DATA:" << data_ << std::endl;

	Tokenizer tokenizer('-');
	auto tokens = tokenizer(data_);

	if(tokens.size() != 2)
		std::cout << "BAD MESSAGE!" << std::endl;
	else
	{
		mediumPort_ = tokens[0];
		lowPort_ = tokens[1];
	}
}

AssociationSetupResponseMsg::~AssociationSetupResponseMsg() {
	// Do nothing
}

} /* namespace messages */
} /* namespace proto */
} /* namespace comuactiv */
