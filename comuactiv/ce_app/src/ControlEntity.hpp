/*
 * ControlEntity.hpp
 *
 *  Created on: 3 May 2015
 *      Author: john
 */

#include <iostream>

#ifndef SRC_CE_APP_CONTROLENTITY_HPP_
#define SRC_CE_APP_CONTROLENTITY_HPP_

using namespace std;

namespace comuactiv {
namespace ce_app {

class ControlEntity {
public:
	static ControlEntity& getInstance();

	void start() {
		cout << "CE Started" << endl;
		while(1);
	}

private:
	ControlEntity();
	ControlEntity(const ControlEntity&) = delete;
	ControlEntity& operator=(const ControlEntity&) = delete;
};

} /* namespace ce_app */
} /* namespace comuactiv */

#endif /* SRC_CE_APP_CONTROLENTITY_HPP_ */
