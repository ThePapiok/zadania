#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>
#include <sys/sem.h>
#include <sys/ipc.h>


#define SIZE_OF_MSG 128				//  maksymalny dlugosc wiadomosci
#define SIZE_OF_NICK 32				// maksymalna dlugosc nicku

void stop_serwer(int signal);       // zatrzymanie serwera za pomoca ctrl+c
void show_serwer(int signal); 		// pokazanie zawartosci serwera za pomoca ctrl+z
void start_serwer(char *name_of_file);	// uruchomienie serwera


struct data{					//////////////			struktura odpowiadająca za dane w pamieci dzielonej
	char shared_data[SIZE_OF_MSG];			//			shared_data - wpisy użytkowników
	char nick[SIZE_OF_NICK];				//			nick - nick uzytkownikow
	int likes;								//			likes - polubienia w danym wpisie
	int slot;								//			slot - ilosc zajetych slotow w serwisie
	int max_slots;							//			max_slots - ilosc wszystkich mozliwych wpisow
	int write;								//			write - ilosc uzytkownikow akutalnie piszacych wpis
} *shared_memory;				//////////////

int id_of_shared_data;        //id pamieci dzielonej
int id_of_semaphore;		//id semafora
int max_slots;	// ilosc slotow podanych w 2 argumencie

int main(int argc, char **argv) 
{
	if(argc==3)								//////////
	{												//
		char *name_of_file=argv[1];					//	jezeli podano wlasciwa liczbe argumentow
		max_slots=strtol(argv[2], NULL, 10);		//	to wykonuje sie start_serwer()
		start_serwer(name_of_file);		// 	z argumentami nazwa pliku i nick uzytkownika
	}										//////////
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

void start_serwer(char *name_of_file)
{
	struct shmid_ds buf;
	long int key_dl;
	if(signal(SIGINT,stop_serwer)==SIG_ERR)		//////
	{												//
		perror("\nBlad - funkcja signal\n");		//		przechwytywania sygnalu ctrl+c
		printf("Numer bledu: %d\n", errno);     	//		kiedy to nastapi wywoluje sie funkcja stop_serwer
		exit(EXIT_FAILURE);							//		w przypadku bledu wykonuje obsluga bledow funkcji signal
	}											//////
	if(signal(SIGTSTP,show_serwer)==SIG_ERR)		//////
	{													//
		perror("\nBlad - funkcja signal\n");			//		przechwytywania sygnalu ctrl+z
		printf("Numer bledu: %d\n", errno);     		//		kiedy to nastapi wywoluje sie funkcja show_serwer
		exit(EXIT_FAILURE);								//		w przypadku bledu wykonuje obsluga bledow funkcji signal
	}												//////
	printf("[Serwer]: Twitter 2.0 (wersja A)\n");	
	printf("[Serwer]: tworze klucz na podstawie pliku %s ...",name_of_file);
	key_t key_of_shared_data=ftok(name_of_file,1);		//		zapisanie pod zmiennna klucza na podstawie nazwy pliku
    if(key_of_shared_data==-1) 			//////
	{										//
	    perror("\nBlad - funkcja ftok\n");	//		obsluga bledow funkcji ftok
		printf("Numer bledu: %d\n", errno); //  
		exit(EXIT_FAILURE);					//
	}									//////
	key_t key_of_semaphore=ftok(name_of_file,2);   //       zapisanie pod zmiennna klucza na podstawie nazwy pliku
	if(key_of_semaphore==-1) 			//////
	{										//
	    perror("\nBlad - funkcja ftok\n");	//		obsluga bledow funkcji ftok
		printf("Numer bledu: %d\n", errno); //  
		exit(EXIT_FAILURE);					//
	}									////// 
	key_dl=key_of_shared_data;
	printf(" OK (klucz: %ld)\n", key_dl);
	printf("[Serwer]: tworze segment pamieci wspolnej na %i wpis",max_slots);
	if(max_slots>=2&&max_slots<=4)
	{
		printf("y");
	}
	else
	{
		printf("ow");
	}
	printf(" po %ib...\n",SIZE_OF_MSG);
	id_of_shared_data=shmget(key_of_shared_data,max_slots*sizeof(struct data),0600|IPC_CREAT|IPC_EXCL);		// tworzy segment pamieci dzielonej
	if(id_of_shared_data==-1) 			//////
	{										//
		perror("Blad - funkcja shmget");	//
		printf("Numer bledu: %d\n", errno); //		obsluga bledow funkcji shmget 
		exit(EXIT_FAILURE);					//
	}									//////
	id_of_semaphore=semget(key_of_semaphore,max_slots,0600|IPC_CREAT|IPC_EXCL);  //tworzy segment max_slots semaforow
	if(id_of_semaphore==-1) 			//////
	{										//
		perror("Blad - funkcja semget\n");	//
		printf("Numer bledu: %d\n", errno); //		obsluga bledow funkcji semget  
		exit(EXIT_FAILURE);					//
	}									//////
	if(shmctl(id_of_shared_data,IPC_STAT,&buf)==-1)			//////
	{															//
		perror("Blad - funkcja shmctl\n");						//		kopiuje informacje o pamieci dzielonej do buf
		printf("Numer bledu: %d\n", errno);     				//		potrzebujemy to buf.shm_segsz ktory da nam rozmiar
		exit(EXIT_FAILURE);										//		w przypadku bledu wykonuje sie obsluga bledow funkcji shmctl
	}														//////
	printf("          OK (id: %d, rozmiar: %zub)\n",id_of_shared_data,buf.shm_segsz);
	printf("[Serwer]: dolaczam pamiec wspolna...");
	shared_memory=(struct data*)shmat(id_of_shared_data,(void*)0, 0); //dolacza segment z pamieci dzielonej
	if(shared_memory==(struct data*)-1) 	//////
	{											//
		perror("Blad - funkcja shmat\n");		//		obsluga bledow funkcji shmat
		printf("Numer bledu: %d\n", errno);    	//
		exit(EXIT_FAILURE);						//
	}										//////
	shared_memory[0].max_slots=max_slots;	
	shared_memory[0].write=0;										
	shared_memory[0].slot=0;
	for(int i=0;i<max_slots;i++)								//////
	{																//
		if(semctl(id_of_semaphore,i,SETVAL,1)==-1)					//		ustawienie wartosci poczatkowej na 1 dla kazdego semafora
		{															//		w przypadku bledu wykonuje sie obsluga bledow funkcji semctl
			perror("Blad - funkcja semctl\n");						//
			printf("Numer bledu: %d\n", errno);     				//
			exit(EXIT_FAILURE);										//
		}															//
	}															//////
	printf(" OK (adres: %lX)\n", (long int)shared_memory);
	printf("[Serwer]: nacisnij Crtl^Z by wyswietlic stan serwisu\n");
    printf("[Serwer]: nacisnij Crtl^C by zakonczyc program\n");
	while(1)
	{
	}
}

void stop_serwer(int signal)
{
	int blad;
	printf("\n[Serwer]: dostalem SIGINT => koncze i sprzatam...");
	printf(" (odlaczenie: ");
	blad=shmdt(shared_memory); 		// 		odlacznie segment z pamieci dzielonej
	if(blad==-1)						//////
	{										//
		perror("Blad - funkcja shmdt\n");	//	obsluga bledow funkcji shmdt
		printf("Numer bledu: %d\n", errno); //  
		exit(EXIT_FAILURE);					//
	}									//////
	else
	{
		printf("OK");
	}
	printf(", usuniecie: ");
	blad=shmctl(id_of_shared_data, IPC_RMID, 0);	// usuwa segment z pamieci dzielonej
	if(blad==-1)						//////
	{										//
		perror("Blad - funkcja shmctl\n");	//	obsluga bledow funkcji shmctl
		printf("Numer bledu: %d\n", errno); //  
		exit(EXIT_FAILURE);					//
	}									//////
	else
	{
		printf("OK");
	}
	printf(")\n");
	if(semctl(id_of_semaphore,max_slots-1,IPC_RMID)==-1)//////	usuwaja sie semafory w przypadku bledu
	{														//	obsluga bledow funkcji semctl
		perror("Blad - funkcja semctl\n");					//	
		printf("Numer bledu: %d\n", errno);					//  
		exit(EXIT_FAILURE);									//
	}													//////
	exit(0);
}

void show_serwer(int signal)
{
	if(shared_memory[0].slot==0)
	{
		printf("\nBrak wpisow\n");
	}
	else
	{
		printf("\n___________  Twitter 2.0:  ___________\n");
		for(int i=0;i<=shared_memory[0].slot-1;i++)     //   wypisywanie wpisow wraz z nickiem oraz iloscia polubien
		{
			printf("[%s]: %s [Polubienia: %i]\n",shared_memory[i].nick,shared_memory[i].shared_data,shared_memory[i].likes);
		}
	}
}