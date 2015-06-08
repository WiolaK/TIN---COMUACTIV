
/*
 * Wioletta Klimczak
 * Client UDP
 */

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdexcept>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>

int main(int argc, char**argv)
{
   int sockfd,n;
   struct sockaddr_in servaddr, cliaddr;
   char sendline[1000];
   char recvline[1000];

   if (argc != 2)
   {
      printf("Nie podano adresu IP\n");
      return -1;
 //     exit(1);
   }

   sockfd=socket(AF_INET,SOCK_DGRAM,0);

   bzero(&servaddr,sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   hostent* hostEntry = gethostbyname(argv[1]);
   memcpy( (char*) &servaddr.sin_addr, (char*)hostEntry->h_addr, hostEntry->h_length);
   servaddr.sin_port=htons(5550);

   while (fgets(sendline,10000,stdin) != NULL)
   {
      printf("TU\n");
      sendto(sockfd,sendline,strlen(sendline),0,
             (struct sockaddr *)&servaddr,sizeof(servaddr));
   }
}

