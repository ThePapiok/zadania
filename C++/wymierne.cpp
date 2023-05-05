#include <iostream>
#include <cmath>
using namespace std;

float suma(float x1,float x2);
float iloczyn(float x1,float x2);
float w_funkcji(float x1);

struct rational
{
   int licznik;
   unsigned int mianownik;
};
struct wielomian
{
    unsigned int stopien;
    rational tab[11];
};

rational x;
wielomian f;

int main()
{
    float x1,maks,tym,maks_i,maks_j;
    bool jest=true;
    cout<<"Stopien:";
    cin>>f.stopien;
    for(int i=f.stopien;i>=0;i--)
    {
        cout<<"Wspolczynnik "<<i<<endl;
        cout<<"Licznik:";
        cin>>f.tab[i].licznik;
        cout<<"Mianownik:";
        cin>>f.tab[i].mianownik;
    }
    for(int i=0;i<=99;i++)
    {
        for(int j=1;i<=99;i++)
        {
            x.licznik=i;
            x.mianownik=j;
            x1=((float)x.licznik/(float)x.mianownik);
            if(jest)
            {
                maks=w_funkcji(x1);
                if(maks<0)
                {
                    maks=-maks;
                    maks_i=i;
                    maks_j=j;
                }
                jest=false;
            }
            else
            {
                tym=w_funkcji(x1);
                if(tym<0)
                {
                    tym=-tym;
                }
                if(tym>maks)
                {
                    maks=tym;
                    maks_i=i;
                    maks_j=j;
                }
            }
        }
    }
    cout<<"Najwieksze a:"<<maks_i<<endl;
    if(maks_i!=0)
    {
        cout<<"Najwieksze b:"<<maks_j<<endl;
    }
    else
    {
        cout<<"Najwieksze b:<1:99)"<<endl;
    }
    cout<<"Wartosc od f(a/b):"<<maks<<endl;
    return 0;
}

float suma(float x1, float x2)
{
    return x1+x2;
}

float iloczyn(float x1,float x2)
{
    return x1*x2;
}
float w_funkcji(float x1)
{
    float a1,a2,pom,s=0;
    for(int i=f.stopien;i>=0;i--)
    {
      a1=((float)f.tab[i].licznik/(float)f.tab[i].mianownik);
      a2=pow(x1,i);
      pom=iloczyn(a1,a2);
      s=suma(s,pom);
    }
    return s;
}
