#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

fstream plik;

int il_p,il=-1;

void sortowanie(int *p,int *q);
void zamiana(int *a,int *b);


int main()
{

    int a;
    plik.open("liczby.txt", ios::in);
    while(!plik.eof())
    {
        plik>>a;
        il++;
    }
    plik.close();
    int *tab=new int[il+1];
    plik.open("liczby.txt", ios::in);
    for(int i=0;i<=il;i++)
    {
        plik>>a;
        tab[i]=a;
    }
    plik.close();
    sortowanie(tab,tab+il+1);
    plik.open("liczby.out", ios::out);
    for(int i=0;i<=il;i++)
    {
        plik<<tab[i]<<endl;
    }
    plik.close();
    delete []tab;
    return 0;
}

void sortowanie(int *p,int *k)
{
    int *j;
    int *ilosc=k+1;
    if(k-p<=4)
    {
        int *a1,*a2;
        bool pierw;
        for(int i=0;i<k-p-1;i++)
        {
            a1=p+i;
            a2=p+i;
            pierw=true;
            for(j=p+i+1;j<=k-1;j++)
            {
                if(pierw)
                {
                    if(*j<*a1)
                    {
                        a2=j;
                        pierw=false;
                    }
                }
                else
                {
                    if(*j<*a2)
                    {
                        a2=j;
                    }
                }
            }
            zamiana(a1,a2);
        }

    }
    else if(il_p<(log(il+1)/log(2)))
    {
        il_p++;
        int *med,*d,*x;
        int *tab=new int [3];
        *tab=*p;
        *(tab+1)=*(p+((k-p)/2));
        *(tab+2)=*k;
        for(int i=0;i<2;i++)
        {
            for(j=tab+1;j<=tab+2-i;j++)
            {
                if(*j<*(j-1))
                {
                    zamiana(j,j-1);
                }
            }
        }
        if(*p!=*(tab+1));
        {
            zamiana(p,tab+1);
        }
        delete []tab;
        d=p;
        x=d;
        for (j=p+1;j<k;j++)
        {
            if (*j<*x)
            {
                d++;
                zamiana(d,j);
            }
        }
        zamiana(p,d);
        sortowanie(p,d);
        sortowanie(d+1,k);
    }
    else
    {
        int *i,*a,*b,*c,*maks,*st;
        bool jest;
        a=p+((k-1-p)/2);
        k=k-1;
        while(k!=p)
        {
            for(i=a;i>=p;i--)
            {
                st=i;
                do
                {
                    b=p+(2*(st-p)+1);
                    c=p+(2*(st-p)+2);
                    jest=false;
                    if(b<=k)
                    {
                        if(c<=k)
                        {
                            if(*b>*c)
                            {
                                maks=b;
                            }
                            else
                            {
                                maks=c;
                            }
                        }
                        else
                        {
                            maks=b;
                        }
                        if(*st<*maks)
                        {
                            zamiana(maks,st);
                            st=maks;
                            jest=true;
                        }
                    }

                }
                while(b<=k&&jest==true);
            }
            zamiana(p,k);
            a=p;
            k=k-1;
        }
    }
}

void zamiana(int *a,int *b)
{
  int tym=*a;
  *a=*b;
  *b=tym;
}
