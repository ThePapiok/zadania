#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include <netdb.h>
#include <string.h>


/* zad. na SK, do modyfikacji
  por. man getaddrinfo */
/* bez pelnej obslugi bledow! */

struct my_msg{
    char name[16];
    char text[255];
};

int main() {

        int sockfd,s;
        int socko;
        u_short my_port;
        struct my_msg msg;
        struct addrinfo hints;
        struct addrinfo *result, *rp;
	struct sockaddr_in *sain,l;
        /* wybieram "unikalny" numer portu dla serwera */
        my_port = 5000 + (getpid() % 10000);
        char str[10];
        sprintf(str, "%d", my_port);
        memset(&hints, 0, sizeof(struct addrinfo));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_DGRAM;
        hints.ai_flags = AI_PASSIVE;
        hints.ai_protocol = 0;
        hints.ai_canonname = NULL;
        hints.ai_addr = NULL;
        hints.ai_next = NULL;
        struct sockaddr_storage g;
	socklen_t dl=sizeof(l);
        s = getaddrinfo((const char*)NULL, str, &hints, &result);
        if(s != 0) {
                fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
                return -1;
        }

        for(rp = result; rp != NULL; rp = rp->ai_next) {
                sockfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sockfd == -1)
                continue;

        if (bind(sockfd, rp->ai_addr, rp->ai_addrlen) == 0)
		sain=(struct sockaddr_in*)(rp->ai_addr);
		printf("%s\n",inet_ntoa(sain->sin_addr));               
		 break;

            close(sockfd);
        }

        freeaddrinfo(result);
        printf("[Serwer]: Utworzone gniazdo, slucham na porcie: %d\n", my_port);

        while(1) {
                recvfrom(sockfd, &msg, sizeof(msg), 0, (struct sockaddr*)&l,&dl);
		socko=socket(AF_INET,SOCK_DGRAM,0);
		
		sendto(sockfd,&msg,sizeof(msg),0,(struct sockaddr*)&l,sizeof(l));
                printf("Wiadomosc od %s: %s\n", msg.name, msg.text);
        }


        return 0;

}
