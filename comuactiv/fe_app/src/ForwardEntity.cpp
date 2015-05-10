/*
 * ForwardEntity.cpp
 *
 *  Created on: 3 May 2015
 *      Author: Jan Kumor
 */

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>

#include <cstring>
#include <iostream>
#include <memory>

#include "../../proto/include/comuactiv/comuactiv.hpp"

#include "ForwardEntity.hpp"


using namespace comuactiv::fe_app;
using namespace comuactiv::proto;

namespace comuactiv {
namespace fe_app {

ForwardEntity::ForwardEntity() {

}

ForwardEntity& ForwardEntity::ForwardEntity::getInstance() {
	static ForwardEntity instance;
	return instance;
}

void ForwardEntity::start(std::string host, std::string highPort) {
	std::cout << "FE Started" << std::endl;
	std::unique_ptr<ComuactivClientSlot> slot(new ComuactivClientSlot(host, highPort));
	slot->run();
}

} /* namespace fe_app */
} /* namespace comuactiv */
