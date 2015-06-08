/*
 * UDPStreamer.cpp
 *
 *  Created on: 8 Jun 2015
 *      Author: Wioletta Klimczak
 */
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <netdb.h>
#include <stdexcept>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>

#include "../../proto/src/utils/Tokenizer.hpp"
#include "UDPStreamer.hpp"

using namespace comuactiv::proto::flowtable;

namespace comuactiv {
namespace fe_app {

UDPStreamer::UDPStreamer(std::string port, pFlowTable table)
: log_("UDPStreamer#"),
  port_(port),
  table_(table) {
	log_("created.");
	pthread_create(&tid, nullptr, &proto::utils::execute, this);
}

UDPStreamer::~UDPStreamer() {
	pthread_join(tid, nullptr);
	log_("thread joined.");
}

void* UDPStreamer::run() {
	int sockfd,n;
	struct sockaddr_in servaddr,cliaddr;
	socklen_t len;
	char mesg[1000];

	sockfd=socket(AF_INET,SOCK_DGRAM,0);

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(atoi(port_.c_str()));
	bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

	log_("Listening on port "+port_+" on INADDR_ANY.");

	for (;;)
	{
		len = sizeof(cliaddr);
		n = recvfrom(sockfd,mesg,1000,0,(struct sockaddr *)&cliaddr,&len);
		std::string clientHost;
		clientHost.assign(inet_ntoa( reinterpret_cast<struct sockaddr_in *>(&cliaddr)->sin_addr ) );

		log_("Packet from " + clientHost);
		std::string target = table_->find(clientHost);
		log_("Rule from flow table: " + clientHost + "->" + target);

		if( target != "drop") {
			auto tokens = proto::utils::Tokenizer(' ')(target);
			if(tokens.size() == 2) {
				std::string targetHost = tokens[0];
				std::string targetPort = tokens[1];
				struct hostent* hostEntry = gethostbyname(targetHost.c_str());
				if (hostEntry == nullptr) {
					std::cerr << targetHost << " : unknown host" << std::endl;
					exit(2);
				}
				memcpy( (char*) &cliaddr.sin_addr, (char*)hostEntry->h_addr, hostEntry->h_length);
				cliaddr.sin_port = htons(atoi(targetPort.c_str()));
				sendto(sockfd,mesg,n,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
				mesg[n] = 0;
			} else {
				log_("Wrong target rule.");
			}
		} else {
			log_("Dropping packet.");
		}
		log_("Received the following:");
		log_(mesg);
		log_("End of packet.");
	}
}

} /* namespace fe_app */
} /* namespace comuactiv */
