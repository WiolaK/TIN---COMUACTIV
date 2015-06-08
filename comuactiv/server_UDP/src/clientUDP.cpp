
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
#include <cstdlib>

using namespace std;

int main(int argc, char**argv)
{
   int sockfd,n;
   struct sockaddr_in servaddr;
   char sendline[1024];
   char recvline[1024];
   int port;

   if (argv[1] == NULL)
   {
      printf("Nie podano numeru IP\n");
      return -1;
   }

   if (argv[2] == NULL)
   {
	printf("Nie podano numeru portu\n");
        return -1;
   }

   port = atoi(argv[2]);

   sockfd=socket(AF_INET,SOCK_DGRAM,0);

   bzero(&servaddr,sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr = inet_addr(argv[1]);
   servaddr.sin_port=htons(port);

   int buf = 1024;

   while (fgets(sendline, buf,stdin) != NULL)
   {
      sendto(sockfd,sendline,strlen(sendline),0,
             (struct sockaddr *)&servaddr,sizeof(servaddr));
      n=recvfrom(sockfd,recvline, buf,0,NULL,NULL);
      recvline[n]=0;
      fputs(recvline,stdout);
   }
}
