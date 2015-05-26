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

/*
 *  Initialization a UDP server object making it ready to receive messages.
 *  The server address and port are specified in the constructor.
 *  The address is a string type.
 *  The socket is open in this process.
 */
ServerUDP::ServerUDP(const std::string& addr, int port) : f_port(port), f_addr(addr) {
// f_port - port on the switch that connects to a node point-to-point
	char decimal_port[16];
	snprintf(decimal_port, sizeof(decimal_port), "%d", f_port);
	decimal_port[sizeof(decimal_port) / sizeof(decimal_port[0]) - 1] = "\0";
	struct addrinfo hints; // structure to contain information about address of a service provider
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC; // protocol family for socket
	hints.ai_socktype = SOCK_DGRAM; // socket type - datagram socket UDP
	hints.ai_protocol = IPPROTO_UDP; // protocol for socet - IPPROTO_UDP

	int r(getaddrinfo(addr.c_str(), decimal_port, &hints, &f_addrinfo));

	if(r != 0 || f_addrinfo == NULL)
	{
		cout << "invalid address or port for UDP socket";
	}

	f_socket = socket(f_addrinfo->ai_family, SOCK_DGRAM | SOCK_CLOEXEC, IPPROTO_UDP); // create a new socket

	if(f_socket == -1)
	{
		freeaddrinfo(f_addrinfo); // free memory
		cout << "Could not create UDP socket";
	}

	r = bind(f_socket, f_addrinfo->ai_addr, f_addrinfo->ai_addrlen); // assign an address to the socket

	if(r != 0)
	{
		freeaddrinfo(f_addrinfo); /// free memory
		close(f_socket); // close descriptor
		cout << "Could not bind UDP socket"
	}
}

ServerUDP::~ServerUDP(){
	freeaddrinfo(f_addrinfo); // free memory
	close(f_socket); // close descriptor
}

// return socket
int ServerUDP::get_socket() const
{
	return f_socket;
}

// return port
int ServerUDP::get_port() const
{
	return f_port;
}

// return address
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
	FD_SET(f_socket, &s); // add f_socket to s collection
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



