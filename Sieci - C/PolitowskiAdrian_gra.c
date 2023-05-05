#include <stdio.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <netdb.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <fcntl.h>
#include <signal.h>

struct game{					//////		
	char player_nick[200];			//		struktura przechowujaca informacje o nicku przeciwnikia,
	int id;							//		swoje id oraz czy runda jest pierwsza
	int first;						//		
};								//////

struct in_game{			//////
	int round;				// 	
	int number;				//	
	char operation[100];	//	struktura przechowujaca informacje o rundzie, o liczbie ktora dodajemy,
	int score[2];			//	opeeracji, wyniku graczy, oraz kto pierwszy zaczyna
	int who;				//
};						//////

void start_game(char *iphost,char *nrport,char *nick,int select_nick); 	// funkcja rozpoczynajaca gre dostaje informacje o ip przeciwnika, portu, swojego nicku oraz czy wybralimsy nick czy nie
void error(int value,char *function,pid_t valuepid); // funkcja sprawdzajaca czy wystapil blad dostaje informacje o wartosc, nazwy funkcji oraz pid potomka jezeli istnieje

int main(int argc, char **argv) 
{

	int select_nick=0;
	char *nick;
	if(argc==3||argc==4)							//////
	{													//
		if(argc==4)										// 	jezeli uzytkownik podal 2 lub 3 argumenty to wykonuje sie funkcja start_game()
		{												//	jezeli uzytkownik podal 3 argumenty to nick jest przekazywany
			select_nick=1;								//
			nick=argv[3];								//
		}												//
		start_game(argv[1],argv[2],nick,select_nick);	//
	}												//////
	else if(argc>4)						//////
	{										//	jezeli uzytkownik podal wiecej niz 3 argumenty wyswietlana jest informacja
		printf("Zbyt duzo argumentow!\n");	//
	}									//////
	else								//////
	{										//	jezeli uzytwkonik podal mniej niz 2 argumenty wyswietlana jest informacja 
		printf("Zbyt malo argumentow!\n");	//
	}									//////
	return 0;
}

void start_game(char *iphost,char *nrport,char *nick,int select_nick)
{
	srand(time(NULL));
	int pipeinfo[2],pipegame[2];
	int player_socket,my_socket;
	struct sockaddr_in player_addr,my_addr;
	struct game my_game,player_game;
	struct in_game info_game;
	char ip[16],my_nick[100],operation[100];
	struct addrinfo hints;
	struct addrinfo *result,*iterator;
	int stop,length,its_number,i,koniec,value,connect=1;
	pid_t valuepid=-2;		// jest ustawiony na -2 w celu sprawdzenia czy powstal potomek
	my_game.first=1;
	player_game.first=1;
	error(pipe(pipeinfo),"pipe",valuepid);	//	utworzenie pipe 
	error(pipe(pipegame),"pipe",valuepid);	//	utworzenie pipe
	memset(&hints,0,sizeof(hints));	// wyzerowanie wartosci hints
	hints.ai_family=AF_INET;   							// ustawienie na IPv4
	hints.ai_socktype=SOCK_DGRAM; 						// ustawienie na UDP
    hints.ai_flags=0;									// brak flag
    hints.ai_protocol=0;								// dowolony protokol
	value=getaddrinfo(iphost,nrport,&hints,&result);		// zapisanie do result wszystkich znalezionych struktur adresowych na podstawie adresu ip przeciwnika, portu i hints.
	if(value!=0)									//////
	{													//	jezeli funckja getaddrinfo wywoluje blad to 
		printf("\nBlad - funkcja getaddrinfo\n");		//	wykonuje sie obsluga bledow
		printf("Tresc bledu: %s\n",gai_strerror(value));//
        exit(EXIT_FAILURE);								//
	}												//////
	for(iterator=result;iterator!=NULL;iterator=iterator->ai_next)								//////
	{																								//
		player_socket=socket(iterator->ai_family,iterator->ai_socktype,iterator->ai_protocol);		//	iteruje po wszystkich znalezionych strukturach adresowych
		if(player_socket==-1)																		//	dopoki nie uda sie zrobic socketu
		{																							//	jezeli sie uda to przekazywany jest adres to player_addr
            continue;																				//
		}																							//
		memcpy(&player_addr,iterator->ai_addr,sizeof(player_addr));									//
        break;																						//
	}																							//////
	if(iterator==NULL)								//////
	{													//	jezeli nie udalo sie zrobic socketu na zadnym adresie to 
		printf("\nBlad - brak znalezionego adresu\n");	//	wykonuje sie obsluga bledow
		exit(EXIT_FAILURE);								//
	}												//////
	freeaddrinfo(result);		// zwalnia result
	memset(&hints,0,sizeof(hints));		// wyzerowanie wartosci hints
	hints.ai_family=AF_INET;   		// ustawienie na IPv4
	hints.ai_socktype=SOCK_DGRAM; 	// ustawienie na UDP
    hints.ai_flags=AI_PASSIVE;		// ustawienie adresu na swoj
    hints.ai_protocol=0;			// dowolny protokol
	hints.ai_canonname=NULL;	//////
	hints.ai_addr=NULL;				//	ustawinie na NULL
	hints.ai_next=NULL;			//////
	value=getaddrinfo((const char*)NULL,nrport,&hints,&result); // zapisanie do result wszystkich znalezionych struktur adresowych na podstawie portu i hints.
	if(value!=0)										//////
	{														//
		printf("\nBlad - funkcja getaddrinfo\n");			//	jezeli funckja getaddrinfo wywoluje blad to 
		printf("Tresc bledu: %s\n",gai_strerror(value));	//	wykonuje sie obsluga bledow
        exit(EXIT_FAILURE);									//
	}													//////
	for(iterator=result;iterator!=NULL;iterator=iterator->ai_next)							//////
	{																							//
		my_socket=socket(iterator->ai_family,iterator->ai_socktype,iterator->ai_protocol);		//
		if(my_socket==-1)																		//
		{																						//	iteruje po wszystkich znalezionych strukturach adresowych
            printf("a\n");																		//	dopoki nie uda sie zrobic socketu i bind 
			continue;																			//	jezeli sie uda to przekazywany jest adres to my_addr
		}																						//
		if(bind(my_socket,iterator->ai_addr,iterator->ai_addrlen)==0)							//
		{																						//
			memcpy(&my_addr,iterator->ai_addr,sizeof(my_addr));									//
            break;																				//
		}																						//
	}																						//////
	if(iterator==NULL)									//////
	{														// jezeli nie udalo sie zrobic socketu na zadnym adresie to 
		printf("\n Blad - brak znalezionego adresu\n");		// wykonuje sie obsluga bledow
		exit(EXIT_FAILURE);									//
	}													//////
	freeaddrinfo(result);			// zwalnia result
	strcpy(ip,inet_ntoa(player_addr.sin_addr));		//////
	if(select_nick==0)									//
	{													//	wstawia nick do struktury player_game
		strcpy(nick,ip);								//	jezeli	nie podano nicku to wstawia ip
	}													//
	strcpy(my_nick,nick);								//
	strcpy(player_game.player_nick,my_nick);		//////
	player_game.id=1;
	my_game.id=0;
	if((valuepid=fork())==0)		// tworzy potomka ktory odpowiada z odbieranie 
	{
		valuepid=getpid();	// nadanie wartosci pid
		koniec=0;
		error(close(pipeinfo[0]),"close",valuepid);		// zamykamy pipeinfo[0] bo potomek nie potrzebuje odczytywania readem 
		error(close(pipegame[0]),"close",valuepid);		//	zamykamy pipeinfo[0] bo potomek nie potrzebuje odczytywania readem 
		do		// wykonywuje sie dopoki uzytkownik nie zakonczy
		{
			error(sendto(player_socket,&player_game,sizeof(player_game),0,(struct sockaddr *)&player_addr,sizeof(player_addr)),"sendto",valuepid);	// wysylanie player_game do przeciwnika potrzebne aby 2 uzytkonwik wyslal do 1 uzytkonwika
			if(connect==1)																										//////
			{																														//	informacja pokazuje sie jedynie po
				printf("Gra w 50, wersja A.\n");																					//	uruchomieniu programu
				printf("Rozpoczynam gre %s z Napisz \"koniec\" by zakonczyc lub \"wynik\" by wyswietlic aktualny wynik.\n",ip);		//
				printf("Propozycja gry wyslana.\n");																				//
				connect=0;																											//
			}																													//////
			error(recvfrom(my_socket,&my_game,sizeof(my_game),0,NULL,NULL),"recvfrom",valuepid);	// odbieranie na my_game 
			if(my_game.id==0)		//////
			{							// jezeli uzytwkonik odrazu po dolaczeniu wychodzi przez koniec
				koniec=1;				//
			}						//////
			else if(my_game.id==1)																														//////
			{																																				//
				player_game.id=2;																															//	wysylnie do 2
				error(sendto(player_socket,&player_game,sizeof(player_game),0,(struct sockaddr *)&player_addr,sizeof(player_addr)),"sendto",valuepid);		//	uzytkownika 
				printf("%s dolaczyl do gry.\n",my_game.player_nick);																						//	niezbednych 
				info_game.number=rand()%10+1;																												//	informacji oraz
				printf("Losowa wartosc poczatkowa: %d, podaj kolejna wartosc.\n",info_game.number);															//	wylosowanie liczby
				info_game.round=1;																															//
				info_game.who=1;																															//
				info_game.score[0]=0;																														//
				info_game.score[1]=0;																														//
				error(sendto(player_socket,&info_game,sizeof(info_game),0,(struct sockaddr *)&player_addr,sizeof(player_addr)),"sendto",valuepid);			//
			}																																			//////
			else																						//////
			{																								//	odebranie przez 2 uzy
				error(recvfrom(my_socket,&info_game,sizeof(info_game),0,NULL,NULL),"recvfrom",valuepid);	//
			}																							//////
			if(my_game.id!=0)	// jezeli udalo sie znalezc przeciwnika
			{
				stop=0;
				error(write(pipeinfo[1],&info_game,sizeof(info_game)),"write",valuepid);	// przkazywanie do rodzica niezbednych informacji info_game
				error(write(pipegame[1],&my_game,sizeof(my_game)),"write",valuepid);		// przkazywanie do rodzica niezbednych informacji my_game
				do
				{	
					error(recvfrom(my_socket,&info_game,sizeof(info_game),0,NULL,NULL),"recvfrom",valuepid);		// odbieranie info_game
					if(strcmp(info_game.operation,"Koniec")==0)															//////
					{																										//	
						stop=1;																								//	wykonuje sie gdy
						printf("%s zakonczyl gre, mozesz poczekac na kolejnego gracza.\n",my_game.player_nick);				//	przeciwnik zakonczyl rozgrywke
						my_game.id=0;																						//
						my_game.first=1;																					//
					}																									//////
					else if(strcmp(info_game.operation,"Wygrana")==0||strcmp(info_game.operation,"Remis")==0)											//////
					{																																		// 	jezeli przeciwnik
						if(strcmp(info_game.operation,"Wygrana")==0)																						//	wygral lub zremisowal
						{																																	//	wypisuje sie 
							printf("Przegrana!\n");																											//	informacja oraz
						}																																	//	runda zaczyna
						else if(strcmp(info_game.operation,"Remis")==0)																						//	sie od osoby
						{																																	//	ktora nie zaczynala
							printf("Remis!\n");																												//	na starcie i tak
						}																																	//	na zmiane
						if(my_game.id==info_game.who)																										//	wysyla do przeciwnka
						{																																	//	informacje info_game
							printf("Zaczynamy kolejna rozgrywke, poczekaj na swoja kolej.\n");																//
						}																																	//
						else																																//
						{																																	//
							printf("Zaczynamy kolejna rozgrywke.\n");																						//
							info_game.number=rand()%10+1;																									//
							printf("Losowa wartosc poczatkowa: %d, podaj kolejna wartosc.\n",info_game.number);												//
						}																																	//
						if(info_game.who==1)																												//
						{																																	//
							info_game.who=2;																												//
							info_game.round=2;																												//
						}																																	//
						else																																//
						{																																	//
							info_game.who=1;																												//
							info_game.round=1;																												//
						}																																	//
						strcpy(info_game.operation,"");																										//
						error(sendto(player_socket,&info_game,sizeof(info_game),0,(struct sockaddr *)&player_addr,sizeof(player_addr)),"sendto",valuepid);	//
					}																																	//////
					else if(strcmp(info_game.operation,"Kill")==0)	//////
					{													//	jezeli uzytkonwik zakonczyl gre
						stop=1;											//	to potomek wychodzi z petli i konczy dzialanie
						koniec=1;										//
					}												//////
					else if(strcmp(info_game.operation,"Brak")==0)														//////
					{																										//	jezeli przeciwnik wpisal poprostu liczbe	
						strcpy(info_game.operation,"");																		//	wypisuje sie informacja
						printf("%s podal wartosc %d, podaj kolejna wartosc.\n",my_game.player_nick,info_game.number);		//
					}																									//////
					error(write(pipeinfo[1],&info_game,sizeof(info_game)),"write",valuepid);		// przekazuje informacje o info_game do rodzica
					error(write(pipegame[1],&my_game,sizeof(my_game)),"write",valuepid);			// przekazuje infromacje o my_game do rodzica
				}
				while(!stop);	
			}
		}
		while(!koniec);
		exit(0);
	}
	else
	{
		if(valuepid==-1)					//////
		{										//
			perror("\nBlad - funkcja fork\n");	//	jezeli nie udalo sie utworzyc potomka
			printf("Numer bledu: %d\n",errno);  //	wykonuje sie obsluga bledow
			exit(EXIT_FAILURE);					//
		}									//////
		stop=0;
		error(close(pipeinfo[1]),"close",valuepid);	// zamykamy pipeinfo[1] bo rodzic nie musi pisac do potomka
		error(close(pipegame[1]),"close",valuepid);	// zamykamy pipegame[1] bo rodzic nie musi pisac do potomka
		error(fcntl(pipeinfo[0],F_SETFL,O_NONBLOCK),"fcntl",valuepid);	// flaga umozliwiajaca nie blokowania funkcji read
		error(fcntl(pipegame[0],F_SETFL,O_NONBLOCK),"fcntl",valuepid);	// flaga umozliwiajaca nie blokowania funckji read
		do		// wykonuje sie dopoki nie wykonamy polecnia koniec
		{
			scanf("%s",operation);
			read(pipeinfo[0],&info_game,sizeof(info_game));		// jezeli jest jakas informacja z info_game to odczytujemy
			read(pipegame[0],&my_game,sizeof(my_game));			//	jezeli jest jakas informacja z my_game to odczytujemy
			if(my_game.first==1)									//////
			{															//	wykonuje sie 2 razy jezeli uzytkownik rozpoczyna
				read(pipeinfo[0],&info_game,sizeof(info_game));			//	pierwszy raz
				read(pipegame[0],&my_game,sizeof(my_game));				//
				my_game.first=0;										//
			}														//////
			if(strcmp(operation,"koniec")==0)		// jezeli uzytkownik wykonuje operacje koniec
			{
				if(my_game.id==0)																									//////
				{																														//	jezeli chce wyjsc a jeszcze nikt
					error(sendto(my_socket,&my_game,sizeof(my_game),0,(struct sockaddr *)&my_addr,sizeof(my_addr)),"sendto",valuepid);	//	nie dolaczyl
				}																													//////
				else																																//////
				{																																		// jezeli chce wyjsc
					strcpy(info_game.operation,"Kill");																									//	powiadamia o tym 
					error(sendto(my_socket,&info_game,sizeof(info_game),0,(struct sockaddr *)&my_addr,sizeof(my_addr)),"sendto",valuepid);				//	przeciwnikia
					strcpy(info_game.operation,"Koniec");																								//
					error(sendto(player_socket,&info_game,sizeof(info_game),0,(struct sockaddr *)&player_addr,sizeof(player_addr)),"sendto",valuepid);	//
				}																																	//////
				stop=1;
			}
			else if(my_game.id!=0)		// jezeli uzytkownik nie jest sam
			{
				if(strcmp(operation,"wynik")==0)					//////
				{														// 
					printf("Ty %d : ",info_game.score[my_game.id-1]);	//
					if(my_game.id==1)									//	jezeli uzytkownik wykonal operacje wynik
					{													//	wyswieltaja sie wyniki rozgrywek graczy
						printf("%d ",info_game.score[1]);				//
					}													//
					else												//
					{													//
						printf("%d ",info_game.score[0]);				//
					}													//
					printf("%s\n",my_game.player_nick);					//
				}													//////
				else 
				{
					its_number=1;				//////
					length=strlen(operation);		//
					for(i=0;i<length;i++)			// sprawdzamy czy podana operacja jest
					{								//	liczba
						if(!isdigit(operation[i]))	//
						{							//
							its_number=0;			//
						}							//
					}							//////
					if(its_number)	// jezeli operacja jest liczba
					{
						if(info_game.round==my_game.id)	// jezeli to jego runda
						{
							value=atoi(operation);		// konwertujemy na liczbe
							if(value==0)											//////
							{															//	jezeli wystapil blad z funkcja atoi()
								printf("\nBlad - funkcja atoi\n");						//	to wykonuje sie obsluga bledow i
								error(kill(valuepid,SIGKILL),"kill",valuepid);			//	usuwamy potomka 	
								exit(EXIT_FAILURE);										//
							}														//////
							if(value-info_game.number>=1&&value-info_game.number<=10)		// jezeli liczba jest w poprawnym zakresie
							{
								info_game.number=value;		// zapisuje liczbe do info_game
								if(info_game.number>=50)	
								{
									if(info_game.number==50)					//////
									{												//	jezeli uzytkownik podal liczbe 50
										printf("Wygrana!\n");						//	to zwieksza sie jego wynik o jeden
										strcpy(info_game.operation,"Wygrana");		//	oraz wypisuje sie informacja
										info_game.score[info_game.round-1]++;		//
									}											//////
									else								//////
									{										//	jezeli uzytkownik podal liczbe wieksza niz 50
										printf("Remis!\n");					//	to wykonuje remis
										strcpy(info_game.operation,"Remis");//
									}									//////
									if(info_game.who==my_game.id)															//////
									{																							//
										printf("Zaczynamy kolejna rozgrywke, poczekaj na swoja kolej.\n");						//	rozpoczecie gry
									}																							//	przechodzi na kolejna osobe
									else																						//
									{																							//
										printf("Zaczynamy kolejna rozgrywke.\n");												//
										info_game.number=rand()%10+1;															//
										printf("Losowa wartosc poczatkowa: %d, podaj kolejna wartosc.\n",info_game.number);		//
									}																						//////
								}
								else								////// 
								{										//
									strcpy(info_game.operation,"Brak");	//
									if(info_game.round==1)				//
									{									//	jezeli jeszcze nie udalo sie osiagnac liczby conajmniej 50
										info_game.round=2;				//	to jest kolejna runda
									}									//
									else								//
									{									//
										info_game.round=1;				//
									}									//
								}									//////
								error(sendto(player_socket,&info_game,sizeof(info_game),0,(struct sockaddr*)&player_addr,sizeof(player_addr)),"sendto",valuepid);	// wyslanie do przeciwnika informacja info_game
							}
							else											//////
							{													//	jezeli uzytkonwnik wybiera liczbe z poza zakresu
								printf("Takiej wartosci nie mozesz wybrac!\n");	//
							}												//////
						}
						else																			//////
						{																					//	jezeli to nie jest tura gracza
							printf("Teraz runda gracza %s, poczekaj na swoja kolej.\n",my_game.player_nick);//
						}																				//////
					}
					else									//////
					{											//	jezeli nie ma dostepnej takiej operacji
						printf("Nie ma takiej operacji!\n");	//
					}										//////
				}
			}
			else																		//////
			{																				// jezeli uzytkownik jest sam
				printf("Nie mozna wykonac polecenia poniewaz nie ma drugiego gracza\n");	//
			}																			//////
		}
		while(!stop);
		error(wait(NULL),"wait",valuepid);		// aby nie powstal process zombie
	}
	error(close(player_socket),"close",valuepid);		//zamykamy player_socket
}

void error(int value,char *function,pid_t valuepid)											//////
{																								//
	if(value==-1)																				//
	{																							//
		char info[]="Blad - funkcja ";															//	przekazanie wartosci do funkcji
		strcat(info,function);																	//	jezeli ta wartosc wynosi -1 to wykonuje sie obsluga bledow funkcji
		printf("\n");																			//	podanej jako argument jezeli jest to funkcja kill to musimy samemu zabic potomka
		perror(info);																			//	jezeli wartosc pid podanej jako argument nie jest równa -2 to znaczy ze zostal
		printf("\nNumer bledu: %d\n", errno); 													//	utworzony potomek i trzeba go usunac zanim zakonczymy program
		if(strcmp(function,"kill")==0)															//
		{																						//
			printf("Funkcja kill zwróciła blad, musisz samemu zabic proces potomka\n");			//
		}																						//
		else																					//
		{																						//
			if(valuepid!=-2)																	//
			{																					//
				error(kill(valuepid,SIGKILL),"kill",valuepid);									//
			}																					//
		}																						//
		exit(EXIT_FAILURE);																		//
	}																							//
}																							//////