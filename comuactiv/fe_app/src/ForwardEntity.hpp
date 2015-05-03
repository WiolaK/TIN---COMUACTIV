/*
 * ForwardEntity.hpp
 *
 *  Created on: 3 May 2015
 *      Author: john
 */

#ifndef SRC_FE_APP_FORWARDENTITY_HPP_
#define SRC_FE_APP_FORWARDENTITY_HPP_

#include <iostream>

namespace comuactiv {
namespace fe_app {

class ForwardEntity {
public:
	static ForwardEntity& getInstance();

	void start() {
		std::cout << "FE Started" << std::endl;
		while(1);
	}

private:
	ForwardEntity();
	ForwardEntity(const ForwardEntity&) = delete;
	ForwardEntity& operator=(const ForwardEntity&) = delete;
};

}
}
#endif /* SRC_FE_APP_FORWARDENTITY_HPP_ */
