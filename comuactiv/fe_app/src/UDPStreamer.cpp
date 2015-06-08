/*
 * UDPStreamer.cpp
 *
 *  Created on: 8 Jun 2015
 *  Author: Wioletta Klimczak
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
using namespace std;

namespace comuactiv {
namespace fe_app {

UDPStreamer::UDPStreamer(string port, pFlowTable table) : print_("UDPStreamer#"), port_(port), table_(table)
{
	pthread_create(&tid, nullptr, &proto::utils::execute, this); // nowy watek
	print_("Utworzono.");
}

UDPStreamer::~UDPStreamer()
{
	pthread_join(tid, nullptr);
	print_("Zakonczenie dzialania watku.");
}

void* UDPStreamer::run() {
	int sockfd,n;
	struct sockaddr_in servaddr,cliaddr; // adres serwera i klienta
	socklen_t len;
	char mesg[1024]; // bufor na komunikat
	char repl[1024]; // bufor na odpowiedz

	sockfd = socket(AF_INET,SOCK_DGRAM, IPPROTO_UDP); // utworzenie gniazda UDP

	if(sockfd == -1)
	{
		printf("Blad podczas inicjalizacji gniazda.\n");
		return nullptr;
	}

	bzero(&servaddr,sizeof(servaddr)); // wyzerowanie adresu serwera

	// informacje o interfejsie
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY); // wszystkie adresy
	servaddr.sin_port=htons(atoi(port_.c_str())); // przekazany port

	// wiazanie, identyfikacja gniazda
	if(bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) == -1)
	{
		printf("Blad podczas wiazania gniazda.\n");
		return nullptr;
	}

	print_("Slucham na porcie " + port_ + "na wszystkich adresach");

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

		// wyslanie potwierdzenia otrzymania pakietu
		strcpy(repl,"Otrzymano pakiet.\n");
		sendto(sockfd, repl, buf, 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));

		// odczytanie hosta klienta
		string clientHost;
		clientHost.assign(inet_ntoa( reinterpret_cast<struct sockaddr_in *>(&cliaddr)->sin_addr ) ); // odczytanie adresu hosta
		print_("Otrzymano pakiet od: " + clientHost);
		mesg[n] = 0;
		print_(mesg);
		print_("koniec pakietu.");

		//znalezienie reguly w tablicy
		string targetRule = table_->find(clientHost); // szukanie reguly dla klienta w naszej FlowTable

		print_("Regula z FlowTable: " + clientHost + "-" + targetRule); // wypisanie reguly

		//Obsluga zgodnie z regułą
		if( targetRule != "drop") {

			//parsowanie
			auto tokens = proto::utils::Tokenizer(' ')(targetRule); // dzielenie stringa po spacjach

			if(tokens.size() == 2) {
				string targetHost = tokens[0]; // adres jako pierwszy
				string targetPort = tokens[1]; // port

				struct hostent* hostEntry = gethostbyname(targetHost.c_str()); // pobranie hosta po adresie

				if (hostEntry == nullptr)
				{
					cerr << targetHost << " : nieznany host " << endl; // nie udalo sie odczytac hosta
				}
				else
				{
					memcpy( (char*) &cliaddr.sin_addr, (char*)hostEntry->h_addr, hostEntry->h_length); // kopiujemy adres do struktury klienta, zeby wiedziec gdzie wyslac
					cliaddr.sin_port = htons(atoi(targetPort.c_str())); // ustawienie portu
					print_("Przekierowanie pakietu do " + targetRule);
					sendto(sockfd,mesg,n,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr)); // wysylamy do klienta dane
					continue;
				}
			} else {
				print_("Podano nie prawidlowa ilosc tokenow."); // nie prawidlowa ilosc tokenow (!= 2)
			}
		}
		print_("Odrzucenie pakietu."); // orzucenie pakietu, regula bylo "drop"
	}

	shutdown(sockfd,2); // zamkniecie gniazda
}

} /* namespace fe_app */
} /* namespace comuactiv */
