/*
 * comuactiv_utils.hpp
 *
 *  Created on: 5 May 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_SRC_UTILS_TYPES_HPP_
#define PROTO_SRC_UTILS_TYPES_HPP_



struct hostent;
struct sockaddr;
struct sockaddr_in;

namespace comuactiv {
namespace proto {
namespace utils {

typedef struct sockaddr_in SocketAddressIn;
typedef struct sockaddr SocketAddress;
typedef struct hostent HostEntry;

} /* namespace utils */
} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_UTILS_TYPES_HPP_ */
