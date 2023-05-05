#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <conio.h>
#include <algorithm>
using namespace std;
string szyfrowanie(string napis);
fstream plik1,plik2;
bool jest[123];
char tab[6][6];

int main()
{
 setlocale( LC_ALL, "" );
 wchar_t klawisz;
 int index,il1=0,il2=0;
 string klucz,alfabet="aąbcćdeęfghijklłmnńoópqrsśtuvwxyzżź ",sciezka="",pom,pom2;
 string napis;
 string pom3;
 cout<<"Podaj klucz: ";
 cin>>klucz;
 system("cls");
 cin.ignore();
 cout<<"[1] - tekst z pliku"<<endl;
 cout<<"[2] - tekst z konsoli"<<endl;
 klawisz=getch();
 system("cls");
 for(int i=0;i<6;i++)
 {
     for(int j=0;j<6;j++)
     {
         if(il1<klucz.length())
         {
            index=(int)klucz[il1];
            if(index<0)
            {
                index=(index*(-1))-13;
            }
            if(jest[index]==0)
            {
                jest[index]=1;
                tab[i][j]=klucz[il1];
            }
            else
            {
                j--;
            }
            il1++;

         }
         else
         {
             index=(int)alfabet[il2];
             if(index<0)
             {
                index=(index*(-1))-13;
             }
             if(jest[index]==0)
             {
                 tab[i][j]=alfabet[il2];
             }
             else
             {
                 j--;
             }
             il2++;
         }
     }
 }
 for(int i=0;i<6;i++)
     {
         for(int j=0;j<6;j++)
         {
             cout<<tab[i][j]<<" ";
         }
         cout<<endl;
     }
 if(klawisz=='2')
 {
     cout<<"Tekst:"<<endl;
     getline(cin,napis);
     cout<<napis<<endl;
     transform(napis.begin(), napis.end(), napis.begin(),::toupper);
     //cout<<"Tekst Zaszyfrowany:"<<endl;
     //cout<<szyfrowanie(napis);
     cout<<endl;

 }
 else
 {
     cout<<"Œcie¿ka: "<<endl;
     cin>>sciezka;
     cout<<"Tekst Zaszyfrowany:"<<endl;
    plik1.open(sciezka.c_str(),ios::in);
    string pom4;
    pom=sciezka+".out";
    plik2.open(pom.c_str(),ios::out);
    while(!plik1.eof())
    {
        getline(plik1,napis);
        pom2=szyfrowanie(napis);
        cout<<pom2<<endl;
        plik2<<pom2<<endl;
    }
    plik1.close();
    plik2.close();

 }

}

string szyfrowanie(string napis)
{
string szyfr="";
int pom,yx1[2],yx2[2];
bool j1,j2;
if(napis.length()%2!=0)
 {
    napis=napis+'x';
 }
 for(int i=0;i<=napis.length()-1;i=i+2)
 {
    if(napis[i]==napis[i+1])
    {
        szyfr=szyfr+napis[i]+napis[i];
    }
    else
    {
        j1=0;
        j2=0;
        for(int j=0;j<6;j++)
        {
            for(int k=0;k<6;k++)
            {
                if(tab[j][k]==napis[i]&&j1==0)
                {
                    yx1[0]=j;
                    yx1[1]=k;
                    j1=true;
                }
                if(tab[j][k]==napis[i+1]&&j2==0)
                {
                    yx2[0]=j;
                    yx2[1]=k;
                    j2=true;
                }
                if(j1==1&&j2==1)
                {
                    j=6;
                    k=6;
                }

            }
        }
        if(yx1[0]==yx2[0])
        {
            yx1[1]++;
            yx2[1]++;
            if(yx1[1]>5)
            {
                yx1[1]=0;
            }
            if(yx2[1]>5)
            {
                yx2[1]=0;
            }
        }
        else if(yx1[1]==yx2[1])
        {
            yx1[0]++;
            yx2[0]++;
            if(yx1[0]>5)
            {
                yx1[0]=0;
            }
            if(yx2[0]>5)
            {
                yx2[0]=0;
            }
        }
        else
        {
            pom=yx1[1];
            yx1[1]=yx2[1];
            yx2[1]=pom;
        }
        szyfr=szyfr+tab[yx1[0]][yx1[1]]+tab[yx2[0]][yx2[1]];
    }
 }
 return szyfr;
}
