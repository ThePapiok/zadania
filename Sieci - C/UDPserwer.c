#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>

/* A. Mroz - zad. na SK, do modyfikacji */
/* bez pelnej obslugi bledow! */

struct my_msg{
    char name[16];
    char text[255];
};

int main() {

       int sockfd;
       u_short my_port;
       struct sockaddr_in server_addr;
       struct in_addr ap;
       struct my_msg msg;
       struct in_addr t;
       /* wybieram "unikalny" numer portu dla serwera */
       my_port = 5000+(getpid()%10000);

       /* tworze gniazdo - na razie tylko czesc "protokol" */
       sockfd = socket(AF_INET, SOCK_DGRAM, 0);

       /* podpinam gniazdo pod  konkretny "adres-lokalny"
          i "proces-lokalny" (= port) */
       inet_aton("158.75.2.10",&server_addr.sin_addr);
       server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
       server_addr.sin_family       = AF_INET;           /* IPv4 */
       server_addr.sin_port        = htons(my_port);    /* moj port */
       if(bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr))==-1)
	   {
		  perror("binding");
		exit(1);	   
	   } 
       printf("%d\n",my_port);
       while(1) {
        recvfrom(sockfd, &msg, sizeof(msg), 0, NULL, NULL);
        printf("Wiadomosc od %s: %s\n", msg.name, msg.text);
       }


       return 0;

}
