#include <stdio.h>
#include <errno.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <pwd.h>
#include <sys/stat.h>
#include <grp.h>
#include <fcntl.h>
#include <unistd.h>
#include <libgen.h>
#include <limits.h>


void mylsla();  //  ./myls
void mylsfile(char *argv); //    ./myls <nazwa_pliku>
void set_mod(int tryb,char *c,struct stat argument);  //  uprawnienia
int dl_int(int temp);  //  ilosc cyfr


int main(int argc,char **argv) 
{
	char *name_of_file;
	if(argc==1)
	{
		mylsla();     //  ./myls
	}
	else if(argc==2)
	{
		name_of_file=argv[1];
		mylsfile(name_of_file);  //    ./myls <nazwa_pliku>
	}
	else
	{
		printf("Za duzo argumentow!\n");
	}
	return 0;
}

void mylsla()
{
	extern int errno;
	struct dirent **namelist;
	struct passwd *pwd;
	struct group *gru;
	struct tm *time_mod;
	struct stat argument,linczek;
	int n,link,len,links_width=0,names_width=0,groups_width=0,sizes_width=0,temp_width;
	int blad;
	n = scandir(".", &namelist,0,alphasort);
	if(n==-1)						   ///////////
	{											//
		perror("Blad - funkcja scandir");		//
		printf("Numer bledu: %d\n", errno);     // 		obsluga bledow z scandir();
		exit(EXIT_FAILURE);						//
												//
	}									//////////
	int links[n],sizes[n];
	char names[n][200],groups[n][200],daty[n][200],pathname[n][200],mods[n][200],c[10],name[400],do_link[200],data[200];
	for(int i=0;i<n;i++)
	{
		link=0;
		name[0]='\0';
		do_link[0]='\0';
		blad=stat(namelist[i]->d_name, &argument);
		printf("%s\n",namelist[i]->d_name);
		if(blad==-1)					//////////////
		{											//
			perror("Blad - funkcja stat()");		//
			printf("Numer bledu: %d\n", errno);     //		 obsluga bledow z stat();
			exit(EXIT_FAILURE);						//
		}								//////////////
		blad=lstat(namelist[i]->d_name, &linczek);
		if(blad==-1)						//////////
		{											//
			perror("Blad - funkcja lstat()");		//
			printf("Numer bledu: %d\n", errno);     // 		obsluga bledow z lstat();
			exit(EXIT_FAILURE);						//
		}									//////////
		if((linczek.st_mode&S_IFMT)==S_IFLNK) //////     
		{										  //
			link=1;								  //  		sprawdza czy plik jest linkiem symbolicznym
			argument=linczek;					  //
		}									  //////	  
		c[0]='\0';
		switch (argument.st_mode&S_IFMT)    ////////// 
		{                                  			//
			case S_IFREG:							//
			{										//
				strcat(c,"-");						//
				break;								//
			}										//
			case S_IFDIR:							//
			{										//
				strcat(c,"d");						//
				break;								//
			}										//
			case S_IFCHR:							//
			{										//
				strcat(c,"c");						//
				break;								//
			} 										//
			case S_IFBLK:							//
			{										//     		sprawdza jaki to typ pliku
				strcat(c,"b");						//
				break;								//
			} 										//
			case S_IFLNK:							//
			{										//
				strcat(c,"l");						//
				break;								//
			}										//
			case S_IFSOCK:							//
			{										//
				strcat(c,"s");						//
				break;								//
			}										//
			case S_IFIFO:							//
			{										//
				strcat(c,"p");						//
				break;								//
			}										//
		}									//////////
		set_mod(0,c,argument);      // ustawia uprawnienia
		strcpy(mods[i],c);
		links[i]=argument.st_nlink;		//////
		temp_width=dl_int(links[i]); 		//  	dl_int() - funkcja liczaca ilosc cyfr.   
		if(temp_width>links_width)			//		zapisuje do tablicy ilosc dowiazan 
		{									//		oraz szuka najwiekszej szerokosci
			links_width=temp_width;			//
		}								//////
		pwd=getpwuid(argument.st_uid);			                           //////////////
		if(pwd==NULL)						////////								   //
		{										  //								   //
			perror("Blad - funkcja getpwuid()");  //								   //
			printf("Numer bledu: %d\n", errno);   // obsluga bledow z getpwuid();	   //
			exit(EXIT_FAILURE);					  //								   //
		}								    ////////								   //
		gid_t gr=pwd->pw_gid;					                                       //
		gru=getgrgid(gr);						                                       //
		if(gru==NULL)						////////								   //
		{										  //                                   //     zapisuje do tablic nazwy
			perror("Blad - funkcja getgrgid()");  //								   // 	  grup oraz nazwy uzytkownika
			printf("Numer bledu: %d\n", errno);   // obsluga bledow z getgrgid();	   //	  oraz szuka najwiekszej
			exit(EXIT_FAILURE);					  //								   //     szerokosci dla grup 
		}									////////								   //     i nazw uzytkownika
		strcpy(names[i],pwd->pw_name);			  									   // 
		if(strlen(names[i])>names_width)		                  					   //		 
		{																			   //		 
			names_width=strlen(names[i]);											   //
		}										                                       //
		strcpy(groups[i],gru->gr_name);												   //
		if(strlen(groups[i])>groups_width)											   //
		{																			   //
			groups_width=strlen(groups[i]);											   //
		}																  ///////////////
		sizes[i]=argument.st_size;	    //////////
		temp_width=dl_int(sizes[i]);			// 		dl_int() - funkcja liczaca ilosc cyfr. 
		if(temp_width>sizes_width)				//   	zapisuje do tablicy rozmiary plikow 
		{										//		oraz szuka najwiekszej szerokosci
			sizes_width=temp_width;				//
		}							   ///////////
		time_mod=localtime(&argument.st_mtime);					           /////////////
		if(time_mod==NULL)					/////////								  //
		{										   //								  //   pobiera czas modyfikacji,
			perror("Blad - funkcja localtime()");  //								  //   ustawia odpowiedni format
			printf("Numer bledu: %d\n", errno);    // obsluga bledow z localtime();	  //   i zapisuje do tablicy
			exit(EXIT_FAILURE);					   //							      //
		}								    /////////					   			  //
		strftime(data,sizeof(data),"%m-%d %H:%M",time_mod);							  //      
		strcpy(daty[i],data);											   /////////////
		strcpy(name,namelist[i]->d_name);										//////////////
		if(link)																			//
		{																					//
			len=readlink(name,do_link,sizeof(do_link)-1);									//		zapisuje do tablicy nazwe 
			if(len==-1)							//////////									//		pliku
			{											//									//
				perror("Blad - funkcja readlink()");	//									//
				printf("Numer bledu: %d\n", errno);     // obsluga bledow z readlink();		//
				exit(EXIT_FAILURE);						//									//     
			}									//////////									//
			do_link[len]='\0';																//		jezeli jest on linkiem 
			strcat(name," -> ");															//      zapisuje takze nazwe
			strcat(name,do_link);															//		pliku na ktory wskazuje  
		}																					//
		strcpy(pathname[i],name);							   				   ///////////////
		free(namelist[i]);
	}
	links_width++;
	groups_width++;
	sizes_width++;
	for(int i=0;i<n;i++)			//wyswietla 
	{
		printf("%s %*d %*s %*s %*d %s %s\n",mods[i],links_width,links[i],names_width,names[i],groups_width,groups[i],sizes_width,sizes[i],daty[i],pathname[i]);
	} 
	free(namelist);
}

void mylsfile(char *argv)
{
	extern int errno;
	struct tm *time_mod;
	struct stat argument,linczek,sub;
	char data[200];
	int normal=0,link=0;
	int blad;
	char *path,znak;
	char name[200];
	DIR* dirp;
    struct dirent* direntp;
	blad=stat(argv,&argument);
	if(blad==-1)								////////
	{												  //
			perror("Blad - funkcja stat()");		  //
			printf("Numer bledu: %d\n", errno);       // 	obsluga bledow z stat();
			exit(EXIT_FAILURE);						  //	
	}											////////
	blad=lstat(argv,&linczek);
	if(blad==-1)							////////
	{											  //
		perror("Blad - funkcja lstat()");		  //
		printf("Numer bledu: %d\n", errno);       // obsluga bledow z lstat();
		exit(EXIT_FAILURE);						  //
	}										////////
	if((linczek.st_mode&S_IFMT)==S_IFLNK)              ///////////   
	{                                                     		//
		link=1;											 		//    sprawdza czy plik jest plikiem sybolicznym
		argument=linczek;								  		//
	}												   ///////////
	printf("Informacje o %s:\n",argv);
	printf("Typ pliku: ");
	if(link)									//////////////
	{														//
		printf("link symboliczny\n");						//
	}														//
	else													//
	{														//
		if((argument.st_mode&S_IFMT)==S_IFREG)				//
		{													//   sprawdza typ pliku i go wyswietla
			normal=1;										//
			printf("zwykly plik\n");						//
		}													//
		else												//
		{													//
			printf("katalog\n");							//
		}													//
	}											//////////////				
	if(link)																///////////////
	{																					 //
		strcpy(name,argv);																 //
		path=realpath(dirname(name),NULL);												 //	 wypisuje sciezke do pliku
		if(path==NULL)						///////////									 //
		{											 //									 //
			perror("Blad - funkcja realpath()");	 //									 //
			printf("Numer bledu: %d\n", errno);      //  obsluga bledow z realpath();	 //
			exit(EXIT_FAILURE);						 //	 								 //
		}									///////////									 //
		strcat(path,"/");																 //
		printf("Sciezka:     %s%s\n",path,argv);										 //
	}																					 //
	else																				 //
	{																					 //
		path=realpath(argv,NULL);			        									 //		jezeli jest on plikiem symbolicznym
		if(path==NULL)						///////////									 //		to wypisuje sciezke do
		{											 //									 //		tego pliku oraz do
			perror("Blad - funkcja realpath()");  	 //									 //		pliku na ktory wskazuje
			printf("Numer bledu: %d\n", errno);      // obsluga bledow z realpath();	 //
			exit(EXIT_FAILURE);						 //									 //
		}									///////////									 //
		printf("Sciezka:     %s\n",path);												 //		 
	}																					 //		
	if(link)																			 //
	{																					 //
		path=realpath(argv,NULL);														 //
		if(path==NULL)						///////////									 //
		{											 //									 //
			perror("Blad - funkcja realpath()");	 //									 //
			printf("Numer bledu: %d\n", errno);      // obsluga bledow z realpath();	 //
			exit(EXIT_FAILURE);						 //									 //
		}									///////////									 //
		printf("Wskazuje na: %s\n",path);												 //
	}																		///////////////
	if(normal||link)						  ////////////////
	{														//
		printf("Rozmiar:     %ld bajt",argument.st_size);	//
		if(argument.st_size>=2&&argument.st_size<=4)		//
		{													//
			printf("y");									//  wyswietla romzmiar pliku w bajtach
		}													//
		else if(argument.st_size>4)							//
		{													//
			printf("ow");									//
		}													//
	}										 /////////////////
	else																//////////////////
	{																					//
		printf("Liczba podkatalogow: ");												//						
		dirp=opendir(".");																//
		if(dirp==NULL)						///////////									//
		{											 //									//
			perror("Blad - funkcja opendir()");		 //									//
			printf("Numer bledu: %d\n", errno);      // obsluga bledow z opendir();		//
			exit(EXIT_FAILURE);						 //									//
		}									///////////									//
		int count=0;																	//
		for(;;) 																		//	
		{																				//		liczy i wyswietla ilosc 
            direntp=readdir(dirp);														//		podkatalogow w katalogu
			blad=stat(direntp->d_name, &sub);											//
			if(direntp==NULL) break;													//
			if(blad==-1)						///////////								//
			{											 //								//
				perror("Blad - funkcja stat()");		 //								//
				printf("Numer bledu: %d\n", errno);      // obsluga bledow z stat();	//
				exit(EXIT_FAILURE);						 //								//
			}									///////////								//
																						//
			if(strcmp(direntp->d_name,".")&&strcmp(direntp->d_name,".."))				//   
			{																			//
				if((sub.st_mode&S_IFMT)==S_IFDIR)										//
				{																		//
					count++;															//
				}																		//
			}																			//
		}																				//
		blad=closedir(dirp);															//
		if(blad==-1)						///////////									//
		{											 //									//
			perror("Blad - funkcja closedir()");	 //									//
			printf("Numer bledu: %d\n", errno);      // obsluga bledow z closedir();	//
			exit(EXIT_FAILURE);						 //									//
		}									///////////									//
		printf("%d",count);																//
	}																	//////////////////
	printf("\n");
	printf("Uprawnienia: uzytkownik: ");
	set_mod(1,"brak",argument);							// wyswietla uprawnienia   
	printf("\n");
	time_mod = localtime(&argument.st_atime);								//////////////
	if(time_mod==NULL)					///////////										//
	{											 //										//
		perror("Blad - funkcja localtime()");	 //										//
		printf("Numer bledu: %d\n", errno);      // obsluga bledow z localtime();		//
		exit(EXIT_FAILURE);						 //										//
	}									///////////										//
	strftime(data,sizeof(data),"%d %B %Y roku o %T",time_mod);							//
	printf("Ostatnio uzywany:        %s\n",data);										//	
	time_mod = localtime(&argument.st_mtime);											//  wyswietla czas kiedy 
	if(time_mod==NULL)					///////////										//  plik byl ostatnio
	{											 //										//  uzywany, modyfikowany i zmieniany
		perror("Blad - funkcja localtime()");	 //										//
		printf("Numer bledu: %d\n", errno);      // obsluga bledow z localtime();		//
		exit(EXIT_FAILURE);						 //										//
	}									///////////										//
	strftime(data,sizeof(data),"%d %B %Y roku o %T",time_mod);							//  
	printf("Ostatnio modyfikowany:   %s\n",data);										//
	time_mod = localtime(&argument.st_ctime);											//
	if(time_mod==NULL)					///////////										//
	{											 //										//
		perror("Blad - funkcja localtime()");	 //										//
		printf("Numer bledu: %d\n", errno);      // obsluga bledow z localtime();		//
		exit(EXIT_FAILURE);						 //										//
	}									///////////										//
	strftime(data,sizeof(data),"%d %B %Y roku o %T",time_mod);							//
	printf("Ostatnio zmieniany stan: %s\n",data);							//////////////
	if(normal)																				//////////////
	{																									//
		printf("Pierwsze 77 znakow:\n");																//
		int plik=open(argv, O_RDONLY);																	//
		if(plik==-1)						///////////													//
		{											 //													//
			perror("Blad - funkcja open()");		 //													//
			printf("Numer bledu: %d\n", errno);      // obsluga bledow z open();						//
			exit(EXIT_FAILURE);						 //													//
		}									///////////													//
		for(int i=1;i<=77;i++)																			// 
		{																								//
			blad=read(plik,&znak,sizeof(znak));															//
			if(blad>0)																					//	wyswietla pierwsze 
			{																							//	77 znaki z pliku
				printf("%c",znak);																		//
			}																							//
			else if(blad==-1)				   ///////////          									//
			{											//												//
				perror("Blad - funkcja read()");		//												//
				printf("Numer bledu: %d\n", errno); 	// obsluga bledow z read();						//
				exit(EXIT_FAILURE);						//												//
			}								   ///////////												//
		}																								//
		blad=close(plik);																				//
		if(blad==-1)						//////////                 									//
		{											//                         							//
			perror("Blad - funkcja close()");		//													//
			printf("Numer bledu: %d\n", errno);     // obsluga bledow z close();						//
			exit(EXIT_FAILURE);						//													//
		}								   ///////////													//
	}																						//////////////
	
}

int dl_int(int temp)
{
	int temp_width=0;			//////////////
	while(temp)								//
	{										//
		temp_width++;						//	liczy ilosc cyfr w liczbie
		temp=temp/10;						//
	}										//
	return temp_width;			//////////////
}

void set_mod(int tryb,char *c,struct stat argument)      
{
	mode_t who,is_read,is_write,is_exec;				//////////////
	for(int j=0;j<=2;j++)											//
	{																//
		if(j==0)													//
		{															//
			who=argument.st_mode&S_IRWXU;							//
			is_read=S_IRUSR;										//
			is_write=S_IWUSR;										//
			is_exec=S_IXUSR;										//
		}															//
		else if(j==1)												//
		{															//
			who=argument.st_mode&S_IRWXG;							//
			is_read=S_IRGRP;										//
			is_write=S_IWGRP;										//
			is_exec=S_IXGRP;										//
			if(tryb)												//
			{														//
				printf(", grupa: ");								//
			}														//  wyswietla lub ustawia w zaleznozci
		}															//	od trybu uprawnienia
		else														//
		{															//		
			if(tryb)												//
			{														//
				printf(", inni: ");									//
			}														//
			who=argument.st_mode&S_IRWXO;							//
			is_read=S_IROTH;										//
			is_write=S_IWOTH;										//
			is_exec=S_IXOTH;										//
		}															//
		if(who&is_read)												//
		{															//
			if(!tryb)												//
			{														//
				strcat(c,"r");										//
			}														//
			else													//
			{														//
				printf("r");										//
			}														//
		}															//
		else if(!tryb)												//
		{															//
			strcat(c,"-");											//
		}															//
		if(who&is_write)											//
		{															//
			if(!tryb)												//
			{														//
				strcat(c,"w");										//
			}														//
			else													//
			{														//
				printf("w");										//
			}														//
		}															//
		else if(!tryb)												//
		{															//
			strcat(c,"-");											//
		}															//
		if(who&is_exec)												//
		{															//
			if(!tryb)												//
			{														//
				strcat(c,"x");										//
			}														//
			else													//
			{														//
				printf("s");										//
			}														//
		}															//
		else if(!tryb)												//
		{															//
			strcat(c,"-");											//
		}															//
	}												//////////////////
}
