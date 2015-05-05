/*
 * comuactiv_utils.hpp
 *
 *  Created on: 5 May 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_SRC_COMUACTIV_UTILS_HPP_
#define PROTO_SRC_COMUACTIV_UTILS_HPP_

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <memory>

namespace comuactiv {
namespace proto {

class ActiveChannel;
class PassiveChannel;

typedef struct sockaddr_in SocketAddressIn;
typedef struct sockaddr SocketAddress;
typedef struct hostent HostEntry;
typedef std::shared_ptr<ActiveChannel> pAChannel;
typedef std::shared_ptr<PassiveChannel> pPChannel;

} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_COMUACTIV_UTILS_HPP_ */
