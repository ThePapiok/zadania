#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<netdb.h>
/* A. Mroz - zad. na SK, do modyfikacji */
/* bez pelnej obslugi bledow! */

struct my_msg{
        char name[16];
        char text[255];
};

int main(int argc, char *argv[]) {

        int sockfd,socko;
        struct sockaddr_in server_addr;
        struct addrinfo hints;
        struct addrinfo *rp,*result,*res;
        struct my_msg msg,od;
        ssize_t bytes;
        int a;
	struct sockaddr_in *sain;
	memset(&hints,0,sizeof(hints));
        hints.ai_flags=0;
        hints.ai_family=AF_INET;
        hints.ai_socktype=SOCK_DGRAM;
        hints.ai_protocol=0;
        getaddrinfo(argv[1],argv[2],&hints,&result);
        for(rp=result;rp!=NULL;rp=rp->ai_next)
        {
                sockfd=socket(rp->ai_family,rp->ai_socktype,rp->ai_protocol);
                if(sockfd==-1)
                {
                        continue;
                }
                if(connect(sockfd,rp->ai_addr,rp->ai_addrlen)!=-1)
                {
                        break;
                }


        }
	freeaddrinfo(result);
        printf("[Klient]: Podaj swoj nick:\n> ");
        fgets(msg.name, 16, stdin);
        msg.name[strlen(msg.name)-1] = '\0';
        printf("[Klient]: Podaj wiadomosc do serwera:\n> ");
        fgets(msg.text, 255, stdin);
        msg.text[strlen(msg.text)-1] = '\0';
        bytes = send(sockfd, &msg, sizeof(msg), 0);
        recvfrom(sockfd,&od,sizeof(od),0,NULL,NULL);
        printf("%s\n",od.text);

        close(sockfd);
        return 0;

}
