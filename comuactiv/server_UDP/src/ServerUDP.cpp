/*
 * Wioletta Klimczak
 * UDP Server
 */

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <netdb.h>
#include <stdexcept>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int main(int argc, char**argv)
{
	int sockfd,n;
	struct sockaddr_in servaddr,cliaddr; // adres serwera i klienta
	socklen_t len;
	char mesg[1024]; // bufor na komunikat
	int port;
	char repl[1024];

	if(argc != 2)
	{
		printf("Nie podano numeru portu:\n");
	}

	port = atoi(argv[1]);
	cout << "Numer portu to: " << port << endl;

	sockfd = socket(AF_INET,SOCK_DGRAM, IPPROTO_UDP); // utworzenie gniazda UDP
	// sockfd = socket(AF_INET,SOCK_DGRAM, 0);

	if(sockfd == -1)
	{
		printf("Blad podczas inicjalizacji gniazda.\n");
		return -1;
	}

	bzero(&servaddr,sizeof(servaddr));

	// informacje o interfejsie
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(port);

	if(bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) == -1)
	{
		printf("Blad podczas wiazania gniazda.\n");
		return -1;
	}

	for (;;)
	{
		len = sizeof(cliaddr); // objetosc struktury adresu
		int buf = 1024; // dlugosc bufora przy odbieraniu

		n = recvfrom(sockfd, mesg, buf, 0, (struct sockaddr *) &cliaddr, &len);

		if(n == -1)
		{
			printf("Blad podczas odbioru komunikatu.\n");
			return -1;
		}

		strcpy(repl,"Potwierdzam otrzymanie komunikatu \n");
		//JKU musiałem zakomentować bo jeśli odpowiada na localhoscie to zapętla się protokól
		//sendto(sockfd, repl, buf, 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));

		printf(".........................................\n");
		mesg[n] = 0;
		printf("Otrzymano nastepujacy komunikat\n");
		printf("%s",mesg);
		printf(".........................................\n");

	}
	shutdown(sockfd,2); // zamkniecie gniazda

}
