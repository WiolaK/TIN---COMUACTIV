/*
 * ControlEntity.hpp
 *
 *  Created on: 3 May 2015
 *      Author: Jan Kumor
 */

#ifndef SRC_CE_APP_CONTROLENTITY_HPP_
#define SRC_CE_APP_CONTROLENTITY_HPP_

#include <string>

#include "../../proto/include/comuactiv/FlowTable.hpp"

namespace comuactiv {
namespace ce_app {

class ControlEntity {
public:
	static ControlEntity& getInstance();

	void start(std::string port);

private:
	ControlEntity();
	ControlEntity(const ControlEntity&) = delete;
	ControlEntity& operator=(const ControlEntity&) = delete;
	proto::flowtable::FlowTable flowtable_;
};

} /* namespace ce_app */
} /* namespace comuactiv */

#endif /* SRC_CE_APP_CONTROLENTITY_HPP_ */
