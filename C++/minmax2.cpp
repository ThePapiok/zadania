#include <iostream>
#include <vector>
using namespace std;

void zamien(int &x,int &y);
void asort(vector <int> &a,int n);
void bsort(vector <int> &b,int n);
void csort(vector <int> &c,int n);



int main()
{
int n,x;
vector <int> a;
vector <int> b;
vector <int> c;
while(cin>>n)
{
for(int i=0;i<n;i++)
{
cin>>x;
a.push_back(x);
b.push_back(x);
c.push_back(x);
}
asort(a,n);
bsort(b,n);
csort(c,n);
a.clear();
b.clear();
c.clear();
}
}


void zamien(int &x,int &y)
{
int temp;
temp=x;
x=y;
y=temp;
}

void asort(vector <int> &a,int n)
{
int il=0;
for(int i=0;i<=n-1;i++)
{
for(int j=n-1;j>i;j--)
{
il++;
if(a[j-1]>a[j])
{
zamien(a[j-1],a[j]);
}
}
}
cout<<"Ilosc porownan dla sortowania a: "<<il<<endl;

}

void bsort(vector <int> &b,int n)
{
int il=0;
bool jest;
for(int i=0;i<=n-1;i++)
{
jest=0;
for(int j=n-1;j>i;j--)
{
il++;
if(b[j-1]>b[j])
{
zamien(b[j-1],b[j]);
jest=1;
}
}
if(jest==0)
{
i=n-1;
}
}
cout<<"Ilosc porownan dla sortowania b: "<<il<<endl;

}


void csort(vector <int> &c,int n)
{
int il=0,straznik=0;
for(int i=0;i<=n-1;i=straznik)
{
straznik=n;
for(int j=n-1;j>i;j--)
{
il++;
if(c[j-1]>c[j])
{
zamien(c[j-1],c[j]);
straznik=j;
}
}
}
cout<<"Ilosc porownan dla sortowania c: "<<il<<endl;

}
