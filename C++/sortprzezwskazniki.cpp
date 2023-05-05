#include <iostream>
#include <ctime>
using namespace std;

void sort1(int *p,int *k);
void sort2(int *p,int *k);
void sort3(int *p,int *k);
void zamien(int *a,int *b);

int main()
{
    srand(time(NULL));
    int *tab= new int [21];
    cout<<"Przed sortowaniem:"<<endl;
    for(int *i=tab;i<tab+20;i++)
    {
        *i=rand();
        cout<<*i<<endl;
    }
    sort1(tab,tab+10);
    cout<<endl<<"Po sortowaniu 1 algorytmem:"<<endl;
    for(int *i=tab;i<tab+20;i++)
    {
        cout<<*i<<endl;
    }
    sort2(tab+10,tab+20);
    cout<<endl<<"Po sortowaniu 2 algorytmem:"<<endl;
    for(int *i=tab;i<tab+20;i++)
    {
        cout<<*i<<endl;
    }
    sort3(tab,tab+20);
    cout<<endl<<"Po sortowaniu 3 algorytmem:"<<endl;
    for(int *i=tab;i<tab+20;i++)
    {
        cout<<*i<<endl;
    }
    delete []tab;
    return 0;
}

void sort1(int *p,int *k)
{
    int *d,*i,*x;
    if (p<k)
    {
        d=p;
        x=d;
        for (i=p+1;i<k;i++)
        {
            if (*i<*x)
            {
                d++;
                zamien(d,i);
            }
        }
        zamien(p,d);
        sort1(p,d);
        sort1(d+1,k);
    }
}

void sort2(int *p,int *k)
{
	int *i,*j;
	for(i=p;i<p+10;i++)
	{
		for(j=p+1;j<k-(i-p);j++)
		{
            if(*(j-1)>*j)
            {
                zamien(j,j-1);
            }
		}
	}
}

void sort3(int *p,int *k)
{
	int *i,*a,*b,*c,*maks,*st,*jest=k+1;
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
                *jest=0;
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
                        zamien(maks,st);
                        st=maks;
                        *jest=1;
                    }
                }

            }
            while(b<=k&&*jest==1);
        }
        zamien(p,k);
        a=p;
        k=k-1;
    }
}

void zamien(int *a,int *b)
{
    int *tym=new int;
    *tym=*a;
    *a=*b;
    *b=*tym;
    delete []tym;
}
