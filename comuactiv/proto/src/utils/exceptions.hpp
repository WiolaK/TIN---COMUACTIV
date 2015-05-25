/*
 * exceptions.hpp
 *
 *  Created on: 25 May 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_SRC_UTILS_EXCEPTIONS_HPP_
#define PROTO_SRC_UTILS_EXCEPTIONS_HPP_

#include <exception>

namespace comuactiv {
namespace proto {
namespace utils {

class connectionEndException : public std::exception {
public:
	connectionEndException() {};

private:

};

} /* namespace utils */
} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_UTILS_EXCEPTIONS_HPP_ */
