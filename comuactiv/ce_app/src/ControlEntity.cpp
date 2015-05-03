/*
 * ControlEntity.cpp
 *
 *  Created on: 3 May 2015
 *      Author: john
 */

#include "ControlEntity.hpp"

using namespace comuactiv::ce_app;

namespace comuactiv {
namespace ce_app {

ControlEntity::ControlEntity() {

}

ControlEntity& ControlEntity::ControlEntity::getInstance() {
	static ControlEntity instance;
	return instance;
}

} /* namespace ce_app */
} /* namespace comuactiv */
