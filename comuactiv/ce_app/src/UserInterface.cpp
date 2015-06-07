/*
 * UserInterface.cpp
 *
 *  Created on: 7 Jun 2015
 *      Author: Jan Kumor
 */

#include "UserInterface.hpp"

namespace comuactiv {
namespace ce_app {

UserInterface::~UserInterface() {
	pthread_join(tid, nullptr);
}

} /* namespace ce_app */
} /* namespace comuactiv */
