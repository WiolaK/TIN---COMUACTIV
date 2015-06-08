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
	struct sockaddr_in servaddr,cliaddr; // adres serwera i klienta
	socklen_t len;
	char mesg[1024]; // bufor na komunikat
	char repl[1024];

	sockfd = socket(AF_INET,SOCK_DGRAM, IPPROTO_UDP); // utworzenie gniazda UDP
	// sockfd = socket(AF_INET,SOCK_DGRAM, 0);

	if(sockfd == -1)
	{
		printf("Blad podczas inicjalizacji gniazda.\n");
		return nullptr;
	}

	bzero(&servaddr,sizeof(servaddr));

	// informacje o interfejsie
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(atoi(port_.c_str()));

	if(bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) == -1)
	{
		printf("Blad podczas wiazania gniazda.\n");
		return nullptr;
	}
	log_("Listening on port "+port_+" on INADDR_ANY.");

	for (;;)
	{
		len = sizeof(cliaddr); // objetosc struktury adresu
		int buf = 1024; // dlugosc bufora przy odbieraniu

		n = recvfrom(sockfd, mesg, buf, 0, (struct sockaddr *) &cliaddr, &len);
		if(n == -1)
		{
			printf("Blad podczas odbioru komunikatu.\n");
			return nullptr;
		}
		//JKU potwierdzenie odbioru
		strcpy(repl,"Packet confirmed.\n");
		sendto(sockfd, repl, buf, 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
		//JKU odczytanie hosta klienta
		std::string clientHost;
		clientHost.assign(inet_ntoa( reinterpret_cast<struct sockaddr_in *>(&cliaddr)->sin_addr ) );
		log_("Packet from " + clientHost);
		mesg[n] = 0;
		log_(mesg);
		log_("End of packet.");
		//JKU znalezienie reguly w tablicy
		std::string targetRule = table_->find(clientHost);
		log_("Rule from flow table: " + clientHost + "->" + targetRule);
		//Obsluga zgodnie z regułą
		if( targetRule != "drop") {
			//JKU parsowanie
			auto tokens = proto::utils::Tokenizer(' ')(targetRule);
			if(tokens.size() == 2) {
				std::string targetHost = tokens[0];
				std::string targetPort = tokens[1];
				struct hostent* hostEntry = gethostbyname(targetHost.c_str());
				if (hostEntry == nullptr) {
					std::cerr << targetHost << " : unknown host" << std::endl;
				} else {
					memcpy( (char*) &cliaddr.sin_addr, (char*)hostEntry->h_addr, hostEntry->h_length);
					cliaddr.sin_port = htons(atoi(targetPort.c_str()));
					log_("Redirecting packet to" + targetRule);
					sendto(sockfd,mesg,n,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
					continue;
				}
			} else {
				log_("Wrong target rule.");
			}
		}
		log_("Dropping packet.");
	}

	shutdown(sockfd,2); // zamkniecie gniazda
}

} /* namespace fe_app */
} /* namespace comuactiv */
