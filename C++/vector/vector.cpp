#include <iostream>
#include <windows.h>
#include "vector.h"

using namespace std;

int main()
{
	Vector v;
	bool exit_vector=true,vector_exists=false;
	int option,n,index,value;
	do
	{
		cout<<"1. Wypisz vector"<<endl;
		cout<<"2. Dodaj vector"<<endl;
		cout<<"3. Ustaw wartosc na danej pozycji"<<endl;
		cout<<"4. Pobierz wartosc z danej pozycji"<<endl;
		cout<<"5. Dodaj wartosc"<<endl;
		cout<<"6. Usun vector"<<endl;
		cout<<"7. Wyjdz"<<endl<<": ";
		cin>>option;
		system("cls");
		switch (option)
		{
			case 1:
			{
				if(vector_exists==1)
                {
                    cout<<v;
                }
				else
				{
					cout<<"Vector nie istnieje"<<endl;
				}
				cin.ignore();
                cin.get();
				break;
			}
			case 2:
			{
				if(vector_exists==0)
                {
                    cout<<"Podaj rozmiar vectora: ";
                    cin>>n;
					v.init(n);
					vector_exists=1;
                }
				else
				{
					cout<<"Vector juz istnieje"<<endl;
					cin.ignore();
					cin.get();
				}
				break;
			}
			case 3:
			{
				if(vector_exists==1)
                {
                    cout<<"Podaj index: ";
					cin>>index;
					cout<<"Podaj wartosc: ";
					cin>>value;
					v[index]=value;
                }
				else
				{
					cout<<"Vector nie istnieje"<<endl;
					cin.ignore();
					cin.get();
				}
				break;
			}
			case 4:
			{
				if(vector_exists==1)
                {
                    cout<<"Podaj index: ";
					cin>>index;
					cout<<"Wartosc wynosi: "<<v[index]<<endl;
                }
				else
				{
					cout<<"Vector nie istnieje"<<endl;
				}
				cin.ignore();
                cin.get();
				break;
			}
			case 5:
			{
				if(vector_exists==1)
                {
                    cout<<"Podaj wartosc: ";
					cin>>value;
					v<<value;
                }
				else
				{
					cout<<"Vector nie istnieje"<<endl;
					cin.ignore();
					cin.get();
				}
				break;
			}
			case 6:
			{
				if(vector_exists==1)
                {
                    v.free();
                    vector_exists=0;
                }
				else
				{
					cout<<"Vector nie istnieje"<<endl;
					cin.ignore();
					cin.get();
				}
				break;
			}
			case 7:
			{
				exit_vector=false;
				break;
			}
			default:
            {
                exit_vector=false;
                break;
            }

		}
        system("cls");
	}
	while(exit_vector);
	return 0;
}

