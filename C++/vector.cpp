#include <iostream>
#include <windows.h>

using namespace std;

struct Vector
{
	int *tab;
	int rozmiar=0;
};

void vector_init(Vector *v,int n);
void vector_set_value(Vector *v,int index,int value);
int vector_get_value(Vector *v,int index);
void vector_append(Vector *v,int value);
void vector_free(Vector *v);
void wypisz(Vector *v);

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
                    wypisz(&v);
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
					vector_init(&v,n);
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
					vector_set_value(&v,index,value);
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
					cout<<"Wartosc wynosi: "<<vector_get_value(&v,index)<<endl;
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
					vector_append(&v,value);
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
                    vector_free(&v);
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

		}
        system("cls");
	}
	while(exit_vector);
	return 0;
}

void vector_init(Vector *v,int n)
{
	v->tab=new int [n];
	v->rozmiar=n;
	for(int i=0;i<n;i++)
	{
		v->tab[i]=0;
	}
}

void vector_set_value(Vector *v,int index,int value)
{
	v->tab[index]=value;
}

int vector_get_value(Vector *v,int index)
{
	return v->tab[index];
}

void vector_append(Vector *v,int value)
{
    int *temp=v->tab;
	v->rozmiar++;
	v->tab=new int[v->rozmiar];
	for(int i=0;i<v->rozmiar-1;i++)
	{
		v->tab[i]=temp[i];
	}
	v->tab[v->rozmiar-1]=value;
	delete []temp;
}

void vector_free(Vector *v)
{
	delete []v->tab;
	v->rozmiar=0;
}

void wypisz(Vector *v)
{
	for(int i=0;i<v->rozmiar;i++)
	{
		cout<<v->tab[i]<<" ";
	}
}
