#include <iostream>
#include <windows.h>


using namespace std;

class Vector
{
	int *tab;
	int rozmiar=0;
	public:
	void init(int n);
	void init(Vector *v);
    void set_value(int index,int value);
    int get_value(int index);
    void append(int value);
    void free();
	int operator[](int index);
    friend ostream& operator<<(ostream& s, const Vector & v);
};

Vector::operator<<(int value)
{
    append(value);
    return *this;
}

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
					v.set_value(index,value);
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

		}
        system("cls");
	}
	while(exit_vector);
	return 0;
}

void Vector::init(int n)
{
	tab=new int [n];
	rozmiar=n;
	for(int i=0;i<n;i++)
	{
		tab[i]=0;
	}
}

void Vector::init(Vector *v)
{
    rozmiar=v->rozmiar;
	tab=new int [rozmiar];
	for(int i=0;i<rozmiar;i++)
	{
		tab[i]=v->tab[i];
	}
}

void Vector::set_value(int index,int value)
{
	tab[index]=value;
}

int Vector::get_value(int index)
{
	return tab[index];
}

void Vector::append(int value)
{
	int *temp=tab;
	rozmiar++;
	tab=new int[rozmiar];
	for(int i=0;i<rozmiar-1;i++)
	{
		tab[i]=temp[i];
	}
	tab[rozmiar-1]=value;
	delete []temp;
}

void Vector::free()
{
	delete []tab;
	rozmiar=0;
}


ostream& operator<<(ostream& s, const Vector & v)
    {
        for (int i=0;i<v.rozmiar;i++)
        {
            s<<v.tab[i]<<" ";
        }
		return s;
    }


int Vector::operator[](int index)
{
    return get_value(index);
}
