/*
 * ForwardEntity.hpp
 *
 *  Created on: 3 May 2015
 *      Author: Jan Kumor
 */

#ifndef SRC_FE_APP_FORWARDENTITY_HPP_
#define SRC_FE_APP_FORWARDENTITY_HPP_

#include <string>

namespace comuactiv {
namespace fe_app {

class ForwardEntity {
public:
	static ForwardEntity& getInstance();

	void start(std::string host, std::string highPort, std::string streamerPort);

private:
	ForwardEntity();
	ForwardEntity(const ForwardEntity&) = delete;
	ForwardEntity& operator=(const ForwardEntity&) = delete;
};

}
}
#endif /* SRC_FE_APP_FORWARDENTITY_HPP_ */
