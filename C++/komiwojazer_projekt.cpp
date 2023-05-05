#include <iostream>
#include <cmath>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <fstream>
using namespace std;

std::chrono::time_point<std::chrono::system_clock> start, koniec;
std::chrono::duration<double> czas;
fstream plik;

struct wierzcholek{
    int a;
    int x;
    int y;
};

int il=1;

vector<vector<float> > macierz_dlugosci;
vector<float> temp;
vector<wierzcholek> Punkt;
vector<bool> odwiedzony;
vector<int> droga;
float dlugosc(wierzcholek a,wierzcholek b);
void oblicz_dlugosci(int N);
void TSP_zachlannie(int N,float &suma,int M);
void two_opt(int N,float &min_dl,int M,int K);
void wypisz(int M,float suma);
float znajdz(int p,int q,int N,float dl);
void zamien(int p,int q);

int main()
{
    int N,M,K;
    float suma=0;
    bool wybor;
    string linia;
    cout<<"[0] - z pliku"<<endl;
    cout<<"[1] - z konsoli"<<endl;
    cin>>wybor;
    if(!wybor)
    {
        cout<<"Podaj sciezke do pliku: ";
        cin>>linia;
        plik.open(linia.c_str(),ios::in);
        for(int i=1;i<=5;i++)
        {
            getline(plik,linia);
        }
        plik>>linia>>linia>>N;
        for(int i=1;i<=3;i++)
        {
            getline(plik,linia);
        }

    }
    else
    {
        cout<<"Podaj N: ";
        cin>>N;
    }
    Punkt.resize(N);
    temp.assign(N,0);
    for(int i=0;i<N;i++)
    {
        macierz_dlugosci.push_back(temp);
        if(wybor)
        {
            cin>>Punkt[i].a>>Punkt[i].x>>Punkt[i].y;
        }
        else
        {
            plik>>Punkt[i].a>>Punkt[i].x>>Punkt[i].y;
        }

    }
    if(!wybor)
    {
        plik.close();
    }
    cout<<"[0-"<<N<<"]"<<endl;
    cout<<"Do ilu wierzcholkow wypisywac: ";
    cin>>M;
    cout<<"Co ile wypisywac: ";
    cin>>K;
    start=std::chrono::system_clock::now();
    oblicz_dlugosci(N);
    TSP_zachlannie(N,suma,M);
    two_opt(N,suma,M,K);
    cout<<endl<<"Program osiagnal granice mozliwosci"<<endl;
    wypisz(M,suma);
    return 0;
}

float dlugosc(wierzcholek a,wierzcholek b)
{
    return sqrt((pow(((a.x)-(b.x)),2))+(pow(((a.y)-(b.y)),2)));
}

void oblicz_dlugosci(int N)
{
    float dl;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(i!=j&&macierz_dlugosci[i][j]==0)
            {
                dl=dlugosc(Punkt[i],Punkt[j]);
                macierz_dlugosci[i][j]=dl;
                macierz_dlugosci[j][i]=dl;
            }
        }
    }
}

void TSP_zachlannie(int N,float &suma,int M)
{
    droga.push_back(0);
    odwiedzony.assign(N,0);
    bool jest_min;
    int index,il_odw=0,i=0;
    float min_dl,pom;
    odwiedzony[0]=1;
    while(il_odw!=N-1)
    {
        jest_min=0;
        for(int j=0;j<N;j++)
        {
            if(odwiedzony[j]==0&&i!=j)
            {
                if(jest_min==0)
                {
                    jest_min=1;
                    min_dl=macierz_dlugosci[i][j];
                    index=j;
                }
                else
                {
                    pom=macierz_dlugosci[i][j];
                    if(pom<min_dl)
                    {
                        min_dl=pom;
                        index=j;
                    }
                }
            }
        }
        odwiedzony[index]=1;
        suma+=min_dl;
        i=index;
        droga.push_back(index);
        il_odw++;
    }
    suma+=macierz_dlugosci[i][0];
    wypisz(M,suma);
}

void two_opt(int N,float &min_dl,int M,int K)
{
    bool znaleziono=1;
    int k=0;
    float min_dl_temp;
    while(znaleziono)
    {
        znaleziono=0;
        for(int i=0;i<N-1;i++)
        {
            for(int j=i+1;j<N;j++)
            {
                min_dl_temp=znajdz(i,j,N,min_dl);
                if (min_dl_temp<min_dl)
                {
                    min_dl=min_dl_temp;
                    znaleziono=1;
                    zamien(i,j);
                    k++;
                    if(k==K)
                    {
                        wypisz(M,min_dl);
                        k=0;
                    }
                }
            }
        }
    }
}

float znajdz(int p,int q,int N,float dl)
{
    float suma1,suma2;
    if(p!=0||q!=N-1)
    {
        if(p-1>=0)
        {
            suma1=macierz_dlugosci[droga[p-1]][droga[q]];
            suma2=macierz_dlugosci[droga[p-1]][droga[p]];
        }
        else
        {
            suma1=macierz_dlugosci[droga[N-1]][droga[q]];
            suma2=macierz_dlugosci[droga[N-1]][droga[p]];
        }
        if(q+1<N)
        {
            suma1=suma1+macierz_dlugosci[droga[p]][droga[q+1]];
            suma2=suma2+macierz_dlugosci[droga[q]][droga[q+1]];
        }
        else
        {
            suma1=suma1+macierz_dlugosci[droga[p]][droga[0]];
            suma2=suma2+macierz_dlugosci[droga[q]][droga[0]];
        }
        if(suma1<suma2)
        {
            dl=dl-(suma2-suma1);
        }
    }
    return dl;
}

void wypisz(int M,float suma)
{
    koniec=std::chrono::system_clock::now();
    czas=koniec-start;
    cout<<il<<" - "<<"K: "<<suma<<", T: "<<czas.count()<<"s, ";
    if(M!=0)
    {
        cout<<Punkt[droga[0]].a;
    }
    for(int i=1;i<M;i++)
    {
        cout<<"->"<<Punkt[droga[i]].a;
    }
    cout<<endl<<endl;
    il++;
}

void zamien(int p,int q)
{
    int pom;
    while(p<q)
    {
        pom=droga[p];
        droga[p]=droga[q];
        droga[q]=pom;
        p++;
        q--;

    }
}
