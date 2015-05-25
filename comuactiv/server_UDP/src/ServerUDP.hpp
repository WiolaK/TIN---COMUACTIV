/*
 * ServerUDP.hpp
 *
 *  Created on: May 24, 2015
 *      Author: Wiola Klimczak
 */

#ifndef SERVER_UDP_SRC_SERVERUDP_HPP_
#define SERVER_UDP_SRC_SERVERUDP_HPP_

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdexcept>

namespace comuactiv{
namespace server_udp{

class ServerUDP {
public:
	static ServerUDP& getInstance();
	ServerUDP(const std::string& addr, int port);
	~ServerUDP();
	int get_socket() const;
	int get_port() const;
	std::string get_addr() const;

	int recv(char *msg, size_t max_size);
	int timed_recv(char *msg, size_t max_size, int max_wait_ms);

private:
//	ServerUDP();
//	virtual ~ServerUDP();
	int f_socket;
	int f_port;
	std::string f_addr;
	struct addrinfo* f_addrinfo;
};

} /* namespace sercer_udp */
} /* namespace comuactiv */

#endif /* SERVER_UDP_SRC_SERVERUDP_HPP_ */
