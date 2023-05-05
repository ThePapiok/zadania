#include <iostream>
#include <map>
#include <fstream>
#include <cmath>
#include <windows.h>
using namespace std;

pair<int,int> p;
map<pair<int,int>,int> temp;
void action(int akcja,map<pair<int,int>,int> &m,map<pair<int,int>,int> k);

class sparse_matrix{
    size_t rows,columns;
    map<pair<int,int>,int> elements;
    public:
    void append(double value,pair<int,int> p)
    {
        if(value!=0)
		{
			elements[p]=value;
		}
    }
	double getvalue(int x,int y)
	{
		p.first=x;
        p.second=y;
        if(elements.count(p))
        {
            return elements[p];
        }
        return 0;

	}
    sparse_matrix(size_t x, size_t y)
    {
        rows=x;
        columns=y;
    }
    double operator()(int x,int y)
    {
        return getvalue(x,y);

    }
    void operator+(sparse_matrix k)
    {
        if(columns==k.columns&&rows==k.rows)
		{
			for(auto i:k.elements)
			{
				if(elements.count(i.first))
				{
					elements[i.first]+=i.second;
					if(elements[i.first]==0)
					{
						elements.erase(i.first);
					}
				}
				else
				{
					elements[i.first]=i.second;
				}
			}
		}
		else
		{
			cout<<"Blad!"<<endl;
		}
    }
    void operator-(sparse_matrix k)
    {
        if(columns==k.columns&&rows==k.rows)
		{
			for(auto i:k.elements)
			{
				if(elements.count(i.first))
				{
					elements[i.first]-=i.second;
					if(elements[i.first]==0)
					{
						elements.erase(i.first);
					}
				}
				else
				{
					elements[i.first]=-i.second;
				}
			}
		}
		else
		{
			cout<<"Blad!"<<endl;
		}
	}
    void operator%(double skalar)
    {
        for(auto i:elements)
        {
            elements[i.first]*=skalar;
        }
    }
    void operator*(sparse_matrix k)
    {
		if(columns==k.rows)
		{
			temp.clear();
			double sum,a,b;
			for(int i=0;i<rows;i++)
			{
				for(int l=0;l<k.columns;l++)
				{
					sum=0;
					for(int j=0;j<columns;j++)
					{
						a=getvalue(j,i);
						b=k.getvalue(l,j);
						sum=sum+a*b;
					}
					if(sum!=0)
					{
						p.first=l;
						p.second=i;
						temp[p]=sum;
					}
				}
			}
			columns=k.columns;
			elements=temp;
		}
		else
		{
			cout<<"Blad!"<<endl;
		}
	}
	void operator/(double skalar)
    {
        if(skalar!=0)
        {
            for(auto i:elements)
            {
                elements[i.first]*=(1/skalar);
            }
        }
		else
		{
			cout<<"Blad!"<<endl;
		}
    }
	void operator=(sparse_matrix k)
    {
        elements=k.elements;
		rows=k.rows;
		columns=k.columns;
    }
    double det()
    {
        return detreq(rows,columns,elements);
    }
	double detreq(size_t rows,size_t columns,map <pair<int,int>,int> macierz)
	{
		if(rows==columns)
		{
			int sum=0;
			if(rows==1)
			{
				p.first=0;
				p.second=0;
				return macierz[p];
			}
			else
			{
				map <pair<int,int>, int> temp_macierz;
				pair<int,int> p_temp;
				int index;
				double value;
				for(int i=0;i<columns;i++)
				{
					temp_macierz.clear();
					p.first=i;
					p.second=0;
					for(int j=1;j<rows;j++)
					{
						index=0;
						for(int k=0;k<columns;k++)
						{
							if(k!=i)
							{
								p_temp.first=k;
								p_temp.second=j;
								if(macierz.count(p_temp))
								{
									value=macierz[p_temp];
									p_temp.first=index;
									p_temp.second=j-1;
									temp_macierz[p_temp]=value;
								}
                                index++;
							}
						}
					}
				sum+=pow(-1,i+1+1)*macierz[p]*detreq(rows-1,columns-1,temp_macierz);
				}
			}
                return sum;
		}
		else
		{
			cout<<"Blad!"<<endl;
			return -1;
		}
	}
	void tran()
	{
	    int temp_id;
		double value;
	    temp.clear();
	    for(auto i:elements)
        {
                value=i.second;
                p=i.first;
                temp_id=p.first;
                p.first=p.second;
                p.second=temp_id;
                temp[p]=value;
        }
        temp_id=rows;
        rows=columns;
        columns=temp_id;
        elements=temp;
	}
	void save()
	{
		fstream plik;
		plik.open("macierz.txt",ios::out);
		plik<<rows<<" "<<columns<<endl;
		for(auto i:elements)
        {
            p=i.first;
            plik<<p.first<<" "<<p.second<<" "<<i.second<<endl;
        }
		plik.close();

	}
	void load()
	{
	    fstream plik;
	    double value;
	    plik.open("macierz.txt",ios::in);
	    elements.clear();
		plik>>rows>>columns;
		while(!plik.eof())
        {
            plik>>p.first>>p.second>>value;
            elements[p]=value;
        }
		plik.close();
	}
    void print()
    {
        for(int i=0;i<rows;i++)
        {
            for(int j=0;j<columns;j++)
            {
                cout<<getvalue(j,i)<<" ";
            }
            cout<<endl;
        }
    }
};

class wektor_kolumnowy: public sparse_matrix
{
	size_t rows,columns;
	int x,y;
    map<pair<int,int>,int> elements;
	public:
    wektor_kolumnowy(size_t x) : sparse_matrix(x,y=1)
    {
        rows=x;
        columns=y;
    }
    double operator()(int y)
    {
        return getvalue(0,y);

    }
};

int main()
{;

	int x,y,akcja;
	bool typ;
	double value;
	cout<<"0 - Macierz"<<endl;
	cout<<"1 - Wektor kolumnowy"<<endl;
	cout<<"Wybierz na czym chcesz przeprowadzac operacje: ";
	cin>>typ;
	system("cls");
	if(!typ)
	{
		cout<<"Tworzenie Podstawowej Macierzy M:"<<endl;
		cout<<"Podaj ilosc wierszy: ";
		cin>>x;
		cout<<"Podaj ilosc kolumn: ";
		cin>>y;
		sparse_matrix m(x,y);
		system("cls");
		cout<<"Wstawianie wartosci: "<<endl;
		for(int i=0;i<x;i++)
		{
			for(int j=0;j<y;j++)
			{
				cout<<"M("<<j<<","<<i<<"): ";
				cin>>value;
				p.first=j;
				p.second=i;
				m.append(value,p);
			}
		}
		system("cls");
		cout<<"Tworzenie Pomocniczej Macierzy K:"<<endl;
		cout<<"Podaj ilosc wierszy: ";
		cin>>x;
		cout<<"Podaj ilosc kolumn: ";
		cin>>y;
		sparse_matrix k(x,y);
		system("cls");
		cout<<"Wstawianie wartosci: "<<endl;
		for(int i=0;i<x;i++)
		{
			for(int j=0;j<y;j++)
			{
				cout<<"K("<<j<<","<<i<<"): ";
				cin>>value;
				p.first=j;
				p.second=i;
				k.append(value,p);
			}
		}
		do
		{
			system("cls");
			cout<<"[Operacje]"<<endl;
			cout<<"0 - Wyswietl Macierz M"<<endl;
			cout<<"1 - Wyswietl Macierz K"<<endl;
			cout<<"2 - Dodaj Macierz K do Macierzy M"<<endl;
			cout<<"3 - Odejmij Macierz K od Macierzy M"<<endl;
			cout<<"4 - Pomnoz Macierz M przez skalar"<<endl;
			cout<<"5 - Podziel Macierz M przez skalar (tak jakby pomnozyc Macierz M przez ulamek)"<<endl;
			cout<<"6 - Pomnoz Macierz M przez Macierz K"<<endl;
			cout<<"7 - Transponuj Macierz M"<<endl;
			cout<<"8 - Wyznacz wyznacznik Macierzy M"<<endl;
			cout<<"9 - Wez wartosc z Macierzy M"<<endl;
			cout<<"10 - Zapisz Macierz M do pliku"<<endl;
			cout<<"11 - Odczytaj z pliku do Macierzy M"<<endl;
			cout<<"12 - Przypisz Macierzy M Macierz K"<<endl;
			cout <<"13 - zakoncz program"<<endl;
			cout<<": ";
			cin>>akcja;
			system("cls");
			if(akcja!=13)
			{
				switch(akcja)
				{
					case 0:
					{
						m.print();
						break;
					}
					case 1:
					{
						k.print();
						break;
					}
					case 2:
					{
						m.print();
						cout<<"+"<<endl;
						k.print();
						cout<<"="<<endl;
						m+k;
						m.print();
						break;
					}
					case 3:
					{
						m.print();
						cout<<"-"<<endl;
						k.print();
						cout<<"="<<endl;
						m-k;
						m.print();
						break;
					}
					case 4:
					{
						cout<<"Podaj liczbe: ";
						cin>>value;
						cout<<value<<endl;
						cout<<"*"<<endl;
						m.print();
						cout<<"="<<endl;
						m%value;
						m.print();
						break;
					}
					case 5:
					{
						cout<<"Podaj liczbe: ";
						cin>>value;
						cout<<"1/"<<value<<endl;
						cout<<"*"<<endl;
						m.print();
						cout<<"="<<endl;
						m/value;
						m.print();
						break;
					}
					case 6:
					{	
						m.print();
						cout<<"*"<<endl;
						k.print();
						cout<<"="<<endl;
						m*k;
						m.print();
						break;
					}
					case 7:
					{
						cout<<"tran("<<endl;
						m.print();
						cout<<")"<<endl;
						cout<<"="<<endl;
						m.tran();
						m.print();
						break;
					}
					case 8:
					{
						cout<<"det("<<endl;
						m.print();
						cout<<")"<<endl;
						cout<<"="<<endl;
						cout<<m.det()<<endl;
						break;
					}
					case 9:
					{
						m.print();
						cout<<"Podaj x: ";
						cin>>x;
						cout<<"Podaj y: ";
						cin>>y;
						cout<<"M("<<x<<","<<y<<"): "<<m(x,y);
						break;
					}
					case 10:
					{
						m.print();
						m.save();
						cout<<"Pomyslnie zapisano"<<endl;
						break;
					}
					case 11:
					{
						m.print();
						m.load();
						cout<<"Pomyslnie odczytano"<<endl;
						m.print();
						break;
					}
					case 12:
					{
						m.print();
						cout<<"="<<endl;
						k.print();
						cout<<endl<<"M:"<<endl;
						m=k;
						m.print();
						break;
					}
					default:
					{
						cout<<"Niestety nie ma takiej operacji"<<endl;
						break;
					}
				}
				cin.ignore();
				cin.get();
			}		
		}
		while(akcja!=13);
	}
	else
	{
			cout<<"Tworzenie Podstawowego Wektora Kolumnowego W:"<<endl;
			cout<<"Podaj ilosc wierszy: ";
			cin>>x;
			wektor_kolumnowy w(x);
			system("cls");
			cout<<"Wstawianie wartosci: "<<endl;
			for(int i=0;i<x;i++)
			{
				cout<<"W("<<i<<"): ";
				cin>>value;
				p.first=0;
				p.second=i;
				w.append(value,p);
			
			}
			system("cls");
			cout<<"Tworzenie Pomocniczego Wektora Kolumnowego R:"<<endl;
			cout<<"Podaj ilosc wierszy: ";
			cin>>x;
			wektor_kolumnowy r(x);
			system("cls");
			cout<<"Wstawianie wartosci: "<<endl;
			for(int i=0;i<x;i++)
			{
				cout<<"R("<<i<<"): ";
				cin>>value;
				p.first=0;
				p.second=i;
				r.append(value,p);
			}
		do
		{
			system("cls");
			cout<<"[Operacje]"<<endl;
			cout<<"0 - Wyswietl Wektor Kolumnowy W"<<endl;
			cout<<"1 - Wyswietl Wektor Kolumnowy R"<<endl;
			cout<<"2 - Dodaj Wektor Kolumnowy R do Wektora Kolumnowego W"<<endl;
			cout<<"3 - Odejmij Wektor Kolumnowy R od Wektora Kolumnowego W"<<endl;
			cout<<"4 - Pomnoz Wektor Kolumnowy W przez skalar"<<endl;
			cout<<"5 - Pomnoz Wektor Kolumnowy W przez ulamek"<<endl;
			cout<<"6 - Pomnoz Wektor Kolumnowy W przez Wektor Kolumnowy R (mozliwe dopiero np. po operacji nr 7)"<<endl;
			cout<<"7 - Transponuj Wektor Kolumnowy W"<<endl;
			cout<<"8 - Wyznacz wyznacznik Wektora Kolumnowego W (mozliwe dopiero np. po operacjach nr 7 i 6)"<<endl;
			cout<<"9 - Wez wartosc z Wektora Kolumnowego W"<<endl;
			cout<<"10 - Zapisz Wektor Kolumnowy W do pliku"<<endl;
			cout<<"11 - Odczytaj z pliku do Wektora Kolumnowego W"<<endl;
			cout<<"12 - Przypisz Wektorowi Kolumnowemu W Wektor Kolumnowy R"<<endl;
			cout <<"13 - zakoncz program"<<endl;
			cout<<": ";
			cin>>akcja;
			system("cls");
			if(akcja!=13)
			{
				switch(akcja)
				{
					case 0:
					{
						w.print();
						break;
					}
					case 1:
					{
						r.print();
						break;
					}
					case 2:
					{
						w.print();
						cout<<"+"<<endl;
						r.print();
						cout<<"="<<endl;
						w+r;
						w.print();
						break;
					}
					case 3:
					{
						w.print();
						cout<<"-"<<endl;
						r.print();
						cout<<"="<<endl;
						w-r;
						w.print();
						break;
					}
					case 4:
					{
						cout<<"Podaj liczbe: ";
						cin>>value;
						cout<<value<<endl;
						cout<<"*"<<endl;
						w.print();
						cout<<"="<<endl;
						w%value;
						w.print();
						break;
					}
					case 5:
					{
						cout<<"Podaj liczbe: ";
						cin>>value;
						cout<<"1/"<<value<<endl;
						cout<<"*"<<endl;
						w.print();
						cout<<"="<<endl;
						w/value;
						w.print();
						break;
					}
					case 6:
					{
						w.print();
						cout<<"*"<<endl;
						w.print();
						cout<<"="<<endl;
						w*r;
						w.print();
						break;
					}
					case 7:
					{
						cout<<"tran("<<endl;
						w.print();
						cout<<")"<<endl;
						cout<<"="<<endl;
						w.tran();
						w.print();
						break;
					}
					case 8:
					{
						cout<<"det("<<endl;
						w.print();
						cout<<")"<<endl;
						cout<<"="<<endl;
						cout<<w.det()<<endl;
						break;
					}
					case 9:
					{
						w.print();
						cout<<"Podaj y: ";
						cin>>y;
						cout<<"W("<<y<<"): "<<w(y);
						break;
					}
					case 10:
					{
						w.print();
						w.save();
						cout<<"Pomyslnie zapisano"<<endl;
						break;
					}
					case 11:
					{
						w.print();
						w.load();
						cout<<"Pomyslnie odczytano"<<endl;
						w.print();
						break;
					}
					case 12:
					{
						w.print();
						cout<<"="<<endl;
						r.print();
						cout<<endl<<"W:"<<endl;
						w=r;
						w.print();
						break;
					}
					default:
					{
						cout<<"Niestety nie ma takiej operacji"<<endl;
						break;
					}
				}
				cin.ignore();
				cin.get();
			}
		}
		while(akcja!=13);
	}
    return 0;
}