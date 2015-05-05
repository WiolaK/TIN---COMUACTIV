/*
 * ControlEntity.hpp
 *
 *  Created on: 3 May 2015
 *      Author: Jan Kumor
 */

#ifndef SRC_CE_APP_CONTROLENTITY_HPP_
#define SRC_CE_APP_CONTROLENTITY_HPP_

namespace comuactiv {
namespace ce_app {

class ControlEntity {
public:
	static ControlEntity& getInstance();

	void start();

private:
	ControlEntity();
	ControlEntity(const ControlEntity&) = delete;
	ControlEntity& operator=(const ControlEntity&) = delete;
};

} /* namespace ce_app */
} /* namespace comuactiv */

#endif /* SRC_CE_APP_CONTROLENTITY_HPP_ */
