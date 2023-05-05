#include <iostream>
#include <ctime>
#include <cmath>

using namespace std;

void sort1(int *p, int *k);
void sort2(int *p, int *k);
void sort3(int *p, int *k);
void zamien(int *a,int *b);


int main()
{
    srand(time(NULL));
    int *tab= new int [20];
    cout<<"Przed Sortowaniem:"<<endl;
    for(int i=0;i<20;i++)
    {
        tab[i]=rand();
        cout<<tab[i]<<endl;
    }
    sort1(tab,tab+10);
    cout<<endl<<"Po sortowaniu 1 algorytmem:"<<endl;
    for(int i=0;i<20;i++)
    {
        cout<<tab[i]<<endl;
    }
    sort2(tab+10,tab+20);
    cout<<endl<<"Po sortowaniu 2 algorytmem:"<<endl;
    for(int i=0;i<20;i++)
    {
        cout<<tab[i]<<endl;
    }
    for(int n = 5;n<=10000;n++)//n: problem size
    {
          long start = System.time();
          sort3(tab,tab+20);
          long end = System.time();
          long totalTime = end - start;
          double ratio = (double) time / (n * n);

    }
    cout<<endl<<"Po sortowaniu 3 algorytmem:"<<endl;
    for(int i=0;i<20;i++)
    {
        cout<<tab[i]<<endl;
    }
    delete []tab;
    return 0;
}

void sort1(int *p, int *k)
{
    int *d, *i, x;
    if (p<k)
    {
        d = p;
        x = *d;
        for (i=p+1; i<k; ++i)
        {
            if (*i<x)
            {
                ++d;
                zamien(d,i);
            }
        }
        zamien(p,d);
        sort1(p,d);
        sort1(d+1,k);
    }
}

void sort2(int *p, int *k)
{
	int i,*j,a,b;
	for(i=0;i<10;i++)
	{
		for(j=p+1;j<k-i;j++)
		{
		a=*j;
		b=*(j-1);
		if(b>a)
		{
			zamien(j,j-1);
		}
		}
	}



}

void sort3(int *p,int *k)
{
	int *i,*a,dwa,*b,*c,*maks,*ko,*st,*st2;
	bool jest;
	dwa=(k-1-p)/2;
    a=p+dwa;
    ko=k-1;
    while(ko!=p)
    {
	for(i=a;i>=p;i--)
	{
        st=i;
        do
        {
            b=p+(2*(st-p)+1);
            c=p+(2*(st-p)+2);
            jest=false;
            if(b<=ko)
            {
                if(c<=ko)
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
                    jest=true;
                    zamien(maks,st);
                    st=maks;
                }
            }

        }
        while(b<=ko&&jest==true);
	}
	zamien(p,ko);
	a=p;
	ko=ko-1;
    }
}

void zamien(int *a,int *b)
{
    int tym=*a;
    *a=*b;
    *b=tym;
}
