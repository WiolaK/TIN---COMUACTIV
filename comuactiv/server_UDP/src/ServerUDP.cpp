/*
 * ServerUDP.cpp
 *
 *  Created on: May 24, 2015
 *      Author: Wiola Klimczak
 */

#include "ServerUDP.hpp"
#include <string.h>
#include <unistd.h>

using namespace std;

namespace comuactiv {
namespace server_udp{

/*
ServerUDP::ServerUDP() {

}

ServerUDP::~ServerUDP() {
	// TODO Auto-generated destructor stub
}
*/

ServerUDP& ServerUDP::ServerUDP::getInstance() {
	static ServerUDP instance;
	return instance;
}

ServerUDP::ServerUDP(const std::string& addr, int port) : f_port(port), f_addr(addr) {
	char decimal_port[16];
	snprintf(decimal_port, sizeof(decimal_port), "%d", f_port);
	decimal_port[sizeof(decimal_port) / sizeof(decimal_port[0]) - 1] = "\0";
	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;

	int r(getaddrinfo(addr.c_str(), decimal_port, &hints, &f_addrinfo));

	if(r != 0 || f_addrinfo == NULL)
	{
		cout << "invalid address or port for UDP socket";
		//throw ServerUDP_runtime_error(("invalid address or port for UDP socket: \" " + addr ":"  + decimal_port + "\"").c_str()
	}

	f_socket = socket(f_addrinfo->ai_family, SOCK_DGRAM | SOCK_CLOEXEC, IPPROTO_UDP);

	if(f_socket == -1)
	{
		freeaddrinfo(f_addrinfo);
		cout << "Could not create UDP socket";
		//throw ServerUDP_runtime_error(("couldn't create UDP socket for: \"" + addr + ":" + decimal_port + "\"").c_str());
	}

	r = bind(f_socket, f_addrinfo->ai_addr, f_addrinfo->ai_addrlen);

	if(r != 0)
	{
		freeaddrinfo(f_addrinfo);
		close(f_socket);
		cout << "Could not bind UDP socket"
		//throw ServerUDP_runtime_error(("couldn't bind UDP socket with: \ "" + addr + ":" + decimal_port + "\"").c_str());
	}
}

ServerUDP::~ServerUDP(){
	freeaddrinfo(f_addrinfo);
	close(f_socket);
}

int ServerUDP::get_socket() const
{
	return f_socket;
}

int ServerUDP::get_port() const
{
	return f_port;
}

std::string ServerUDP::get_addr() const
{
	return f_addr;
}

int ServerUDP::recv(char *msg, size_t max_size)
{
	return ::recv(f_socket, msg, max_size, 0);
}

int ServerUDP::timed_recv(char *msg, size_t max_size, int max_wait_ms)
{
	fd_set s;
	FD_ZERO(&s);
	FD_SET(f_socket, &s);
	struct timeval timeout;
	timeout.tv_sec = max_wait_ms / 1000;
	timeout.tv_usec = (max_wait_ms % 1000) * 1000;
	int retval = select(f_socket + 1, &s, &s, &s, &timeout);

	if(retval == -1)
	{
		return -1;
	}

	if(retval > 0)
	{
		return ::recv(f_socket, msg, max_size, 0);
	}

	// errno = EAGAIN; // błąd - zasób tymczasowo niedostępny
	return -1;
}


} /* namespace ServerUDP */
} /* namespace comuactiv */



