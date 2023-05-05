#include <iostream>
using namespace std;

int euklides(int x,int y,int &pom,int &x1,int &x2,int p)
{
    int tym;
    int q=y/x;
    int r=y%x;
    int ret;
    if(r!=0)
    {
        p++;
        euklides(r,x,pom,x1,x2,p);
        p--;
    }
    else
    {
        ret=x;
        pom=x;
        x1=0;
        x2=1;
    }
    if(r!=0)
    {
        tym=x1;
        x1=x2;
        x2=tym+(x2*(-q));
    }
    if(p==0)
    {
        tym=x1;
        x1=x2;
        x2=tym;
        if(x2<x1&&(x2*x+x1*y==pom))
        {
            tym=x1;
            x1=x2;
            x2=tym;
        }
        cout<<x1<<" "<<x2;
        cout<<" "<<pom<<endl;
    }
    return ret;
}

int main()
{
    int x1,x2,a,b,p;
    while(cin>>a>>b)
    {
        p=0;
        euklides(a,b,a,x1,x2,p);
    }
    return 0;
}
