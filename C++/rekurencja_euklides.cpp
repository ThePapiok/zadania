#include <iostream>

using namespace std;

void euklides(unsigned long long int &a, unsigned long long int &b)
{
    unsigned long long int r,d;
    do
    {
      r=b%a;
      d=b/a;
      cout<<b<<" = "<<d<<" * "<<a<<" + "<<r<<endl;
      b=a;
      a=r;

    }
    while(r!=0);

}

int main()
{

unsigned long long int a,b;
cin>>a>>b;
euklides(a,b);
return 0;
}
