/*
 * comuactiv_utils.hpp
 *
 *  Created on: 5 May 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_SRC_COMUACTIV_UTILS_HPP_
#define PROTO_SRC_COMUACTIV_UTILS_HPP_

struct hostent;
struct sockaddr;
struct sockaddr_in;

namespace comuactiv {
namespace proto {

typedef struct sockaddr_in SocketAddressIn;
typedef struct sockaddr SocketAddress;
typedef struct hostent HostEntry;

} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_COMUACTIV_UTILS_HPP_ */
