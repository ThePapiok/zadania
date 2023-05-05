#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/sem.h>
#include <unistd.h>

#define SIZE_OF_MSG 128					//  maksymalny dlugosc wiadomosci
#define SIZE_OF_NICK 32					// maksymalna dlugosc nicku

void open_klient(char *name_of_file,char *nick);		//funkcja sluzaca do obslugi klienta
	
struct data{					//////////////			struktura odpowiadająca za dane w pamieci dzielonej
	char shared_data[SIZE_OF_MSG];			//			shared_data - wpisy użytkowników
	char nick[SIZE_OF_NICK];				//			nick - nick uzytkownikow
	int likes;								//			likes - polubienia w danym wpisie
	int slot;								//			slot - ilosc zajetych slotow w serwisie
	int max_slots;							//			max_slots - ilosc wszystkich mozliwych wpisow
	int write;								//			write - ilosc uzytkownikow akutalnie piszacych wpis
} *shared_memory;				//////////////

int id_of_shared_data;        //id wspolnej pamieci
int id_of_semaphore;		//id semafora


int main(int argc, char **argv) 
{
	if(argc==3)					//////////
	{									//		jezeli podano wlasciwa liczbe argumentow 
		char *name_of_file=argv[1];		//		to wykonuje sie open_klient()
		char *nick=argv[2];				//		z argumentami nazwa pliku i nick uzytkownika
		open_klient(name_of_file,nick);	//
	}							//////////
	else if(argc<3)						//////
	{										//	jezeli ilosc argumentow jest zbyt mala 
		printf("Zbyt malo argumentow!\n");	//  to pojawia sie informacja
	}									//////
	else 									//////
	{											//	jezeli ilosc argumentow jest zbyt duza
		printf("Zbyt duzo argumentow!\n");		//	to pojawia sie informacja
	}										//////
	return 0;
}

void open_klient(char *name_of_file,char *nick)
{
	union semun 
	{
	 int val;	
	}arg;
	key_t key_of_shared_data=ftok(name_of_file,1);		// zapisanie klucza do zmiennnej na podstawie nazwy pliku
	key_t key_of_semaphore=ftok(name_of_file,2);     // zapisanie klucza do zmiennnej na podstawie nazwy pliku
	char akcja,text[SIZE_OF_MSG];		// akcja - wybor uzytkownika (nowy wpis lub polubienie istniejacego),  text[]- pole do wpisu uzytkownika
	int free_slots,temp_slot,like,value;       //  free_slots - ilosc dostepnych slotow,temp_slot - tymczasowa zmienia do przechowywania indexu, value- aktualna wartosc semafora
    if(key_of_shared_data==-1) 				//////
	{											//
	    perror("\nBlad - funkcja ftok\n");		// obsluga bledow z ftok
		printf("Numer bledu: %d\n", errno);    	//
		exit(EXIT_FAILURE);						//
	}										//////
	if(key_of_semaphore==-1) 				//////
	{											//
	    perror("\nBlad - funkcja ftok\n");		// obsluga bledow z ftok
		printf("Numer bledu: %d\n", errno);    	//
		exit(EXIT_FAILURE);						//
	}										//////
	id_of_shared_data=shmget(key_of_shared_data, 0, 0);			//  zapisuje do zmiennnej id segmentu z pamieci dzielonej
	if(id_of_shared_data==-1)			//////
	{										//
		perror("Blad - funkcja shmget\n");	//
		printf("Numer bledu: %d\n", errno); //	obsluga bledow z shmget  
		exit(EXIT_FAILURE);					//
	}									//////
	shared_memory=(struct data*)shmat(id_of_shared_data,(void*)0,0);      //  dolaczenie segmentu z pamieci dzielonej
	if(shared_memory==(struct data*)-1) 	//////
	{											//
		perror("Blad - funkcja shmat\n");		//		obsluga bledow funkcji shmat
		printf("Numer bledu: %d\n", errno);     //
		exit(EXIT_FAILURE);						//
	}										//////
	id_of_semaphore=semget(key_of_semaphore, shared_memory[0].max_slots, 0); //  zapisuje do zmiennnej id segmentu z semaforow
	if(id_of_semaphore==-1)				//////
	{										//
		perror("Blad - funkcja semget\n");	//
		printf("Numer bledu: %d\n", errno); //	obsluga bledow z semget  
		exit(EXIT_FAILURE);					//
	}									//////
	printf("Twitter 2.0 wita! (wersja C)\n");
	free_slots=shared_memory[0].max_slots-shared_memory[0].slot;		// wolne sloty = wszystkie sloty - zajete sloty
	printf("[Wolnych %i wpis",free_slots);
	if(free_slots>=2&&free_slots<=4)
	{
		printf("y");
	}
	else
	{
		printf("ow");
	}
	printf(" (na %i)]\n",shared_memory[0].max_slots);
	if(shared_memory[0].slot!=0)	
	{
		printf("Istniejące wpisy\n");
		for(int i=0;i<=shared_memory[0].slot-1;i++)  // wypisywanie istniejacych wpisow wraz z nickiem wpisem i iloscia polubien
		{
			printf("    %i.  %s [Autor: %s, Polubienia: %i]\n",i+1,shared_memory[i].shared_data,shared_memory[i].nick,shared_memory[i].likes);
		}
	}
	printf("Podaj akcje (N)owy wpis, (L)ike\n");
	scanf("%c",&akcja);
	if(akcja=='N')
	{
		if(free_slots==0)
		{
			printf("Brak wolnych miejsc na stworzenie nowego wpisu\n");
		}
		else
		{
			if(shared_memory[0].write+1+shared_memory[0].slot>shared_memory[0].max_slots)	//////
			{																					//	sprawdza czy w danej chwili nie beda zajete
				printf("Brak wolnych miejsc na stworzenie nowego wpisu\n");						//  wszystkie sloty gdy reszta uzytkownikow skonczy 
			}																				//////	pisac
			else	
			{
				printf("Napisz co ci chodzi po głowie:\n");
				shared_memory[0].write++;		// dodaje uzytkownika jako osobe aktualnie piszaca wpis
				scanf(" ");
				fgets(text,SIZE_OF_MSG,stdin);		//	przekazania wpisanej wiadomosci do zmiennej text
				text[strlen(text)-1]='\0';
				temp_slot=shared_memory[0].slot;		
				value=semctl(id_of_semaphore,temp_slot,GETVAL,arg);					//////
				if(value==-1)															//
				{																		//		pobiera wartosc semafora na aktualnym mozliwie
					shared_memory[0].write--;											//		dostepnym
					perror("Blad - funkcja semctl\n");									//		jesli jest blad to odejmuje uzytkownika z osob
					printf("Numer bledu: %d\n", errno);     							//		aktualnie piszacych wpis i wykonuje sie obsluga 
					exit(EXIT_FAILURE);													//		bledow funkcji semctl
				}																	//////
				while(value==0)															//////
				{																			//	jezeli jednak semafor jest zajety to szuka
					temp_slot++;															//	semafora ktory nie jest zajety pobierajac
					value=semctl(id_of_semaphore,temp_slot,GETVAL,arg);						//
					if(value==-1)															//	wartosc kolejnych semaforow i sprawdzajac
					{																		//	czy sa zajete czy nie konczy na pierwszym
						shared_memory[0].write--;											// 	napotkanym wolnym semaforze
						perror("Blad - funkcja semctl\n");									//	jesli jest blad to odejmuje uzytkownika z osob
						printf("Numer bledu: %d\n", errno);     							//	aktualnie piszacych wpis i wykonuje sie obsluga 
						exit(EXIT_FAILURE);													//	bledow funkcji semctl
																							//
					}																		//
				}																		//////
				struct sembuf sb = {temp_slot, -1, 0};		
				if(semop(id_of_semaphore,&sb,1)==-1) 												//////
				{ 																						//		ustawia semafor na zajety
					shared_memory[0].write--;															//		jesli jest blad to 	odejmuje uzytkownika z osob
					perror("Blad - funkcja semop\n");													//		aktualnie piszacych wpis i wykonuje sie obsluga 
					printf("Numer bledu: %d\n", errno);     											//		bledow funkcji semop
					exit(EXIT_FAILURE);																	// 
				}																					//////
				shared_memory[0].slot++;																//////
				strcpy(shared_memory[temp_slot].shared_data,text);											//	dodanie nowego slotu do pamieci dzielonej
				strcpy(shared_memory[temp_slot].nick,nick);													//	w tym nick, wpis, polubienia, zwiekszenie zajetch slotow o 1
				shared_memory[temp_slot].likes=0;															//	i odejmuje uzytkownika z osob aktualnie piszacych wpis
				shared_memory[0].write--;																//////
				sb.sem_op=1;
				if(semop(id_of_semaphore,&sb,1)==-1) 												//////
				{ 																						//		ustawia semafor na wolny jesli jest blad to
					perror("Blad - funkcja semop\n");													//		wykonuje sie obsluga 
					printf("Numer bledu: %d\n", errno);     											//		bledow funkcji semop
					exit(EXIT_FAILURE);																	// 
				}																					//////
				if(shmdt(shared_memory)==-1)			//////
				{											//	odlaczenie segmentu z pamieci dzielonej
					perror("Blad - funkcja shmdt\n");		//	jesli jest blad to wykonuje sie obsluga 
					printf("Numer bledu: %d\n", errno);     //	bledow funkcji shmdt
					exit(EXIT_FAILURE);						//
				}										//////
				
			}
		}
	}
	else if(akcja=='L')
	{
		if(shared_memory[0].slot==0)
		{
			printf("Nie ma zadnych wpisow aby polubic\n");
		}
		else
		{
			printf("Który wpis chcesz polubic\n");
			scanf("%i",&like);
			if(like<1||like>shared_memory[0].slot)		//////
			{												//	sprawdza czy jest taki wpis aby mozna polubic
				printf("Pod takim numerem nie ma wpisu\n");	//
			}											//////
			else
			{
				shared_memory[like-1].likes++;	//	dodaje polubienie do wybranego wpisu
				if(shmdt(shared_memory)==-1)			//////
				{											//
					perror("Blad - funkcja shmdt\n");		//	odlaczenie segmentu z pamieci dzielonej
					printf("Numer bledu: %d\n", errno);     //	jesli jest blad to wykonuje sie obsluga
					exit(EXIT_FAILURE);						//	bledow funkcji shmdt
				}										//////
			}
		}
	}
	else
	{
		printf("Nie ma takiej akcji\n");
	}
	printf("Dziekuje za skorzystanie z aplikacji Twitter 2.0\n");
}