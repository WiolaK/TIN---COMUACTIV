/*
 * ForwardEntity.cpp
 *
 *  Created on: 3 May 2015
 *      Author: john
 */

#include "ForwardEntity.hpp"

using namespace comuactiv::fe_app;

namespace comuactiv {
namespace fe_app {

ForwardEntity::ForwardEntity() {

}

ForwardEntity& ForwardEntity::ForwardEntity::getInstance() {
	static ForwardEntity instance;
	return instance;
}

} /* namespace fe_app */
} /* namespace comuactiv */
