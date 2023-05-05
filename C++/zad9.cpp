#include <iostream>
#include <fstream>

using namespace std;
fstream plik1,plik2;

int main()
{
char znak;
string nazwa,nazwa_oc,linia;
cout<<"Podaj nazwe:"<<endl;
cin>>nazwa;
nazwa_oc=nazwa+"ocenzurowany.txt";
nazwa=nazwa+".txt";
plik1.open(nazwa.c_str(),ios::in);
plik2.open(nazwa_oc.c_str(),ios::out);
while(getline(plik1,linia))
{
for(int i=0;i<linia.length();i++)
{
znak=linia[i];
if((int)znak>=48&&(int)znak<=57)
{
plik2<<"x";
}
else
{
plik2<<linia[i];
}

}
plik2<<endl;

}
plik1.close();
plik2.close();

return 0;
}
