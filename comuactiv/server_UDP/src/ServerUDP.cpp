
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
#include <iostream>
#include <cstdlib>

int main(int argc, char**argv)
{
   if( argc < 2 ) {
	   printf("Nie podano portu.");
	   return 1;
   }
   int sockfd,n;
   struct sockaddr_in servaddr,cliaddr;
   socklen_t len;
   char mesg[1000];

   sockfd=socket(AF_INET,SOCK_DGRAM,0);

   bzero(&servaddr,sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
   servaddr.sin_port=htons(atoi(argv[1]));
   bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

   for (;;)
   {
      len = sizeof(cliaddr);
      n = recvfrom(sockfd,mesg,1000,0,(struct sockaddr *)&cliaddr,&len);
      //sendto(sockfd,mesg,n,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
      printf("..............\n");
      mesg[n] = 0;
      printf("Received the following:\n");
      printf("%s",mesg);
      printf("..............\n");
   }
}
