#include <iostream>
using namespace std;


void wypisz(string znaki,int mn,string tab)
{
   char tym;
   char znak;
   int k=2;
   for(int i=1;i<=mn;i++)
   {
       cout<<tab;
   }
   if(mn==znaki.length())
   {

        cout<<"writeln(";
        for(int i=0;i<znaki.length();i++)
        {
            cout<<znaki[i];
            if(znaki.length()-1!=i)
            {
                cout<<",";
            }
        }
        cout<<")"<<endl;
   }
   else
   {
        cout<<"if "<<znaki[mn-1]<<" < "<<znaki[mn]<<" then"<<endl;
        znak=znaki[mn];
        wypisz(znaki,mn+1,tab);
    for(int j=mn;j>=0;j--)
    {
        if(mn-k>=0)
        {
        for(int i=1;i<=mn;i++)
        {
            cout<<tab;
        }
        tym=znaki[mn+2-k];
        znaki[mn+2-k]=znaki[mn+1-k];
        znaki[mn+1-k]=tym;
        cout<<"else if "<<znaki[mn-k]<<" < "<<znak<<" then"<<endl;
        k++;
        wypisz(znaki,mn+1,tab);
        }
    }
    if(mn-k<0)
   {
     for(int i=1;i<=mn;i++)
    {
        cout<<tab;
    }
    cout<<"else"<<endl;
    tym=znaki[0];
    znaki[0]=znaki[1];
    znaki[1]=tym;
    wypisz(znaki,mn+1,tab);
   }
   }

}



int main()
{
int M,n,mn=1;
string tab="  ",znaki;
cin>>M;
for(int i=1;i<=M;i++)
{
if(i>1)
{
    cout<<endl;
}
cin>>n;
znaki="";
for(int j=0;j<n;j++)
{
    znaki=znaki+char(97+j);
}
cout<<"program sort(input,output);"<<endl;
cout<<"var"<<endl;
for(int j=0;j<znaki.length();j++)
{
    cout<<znaki[j];
    if(znaki.length()-1!=j)
    {
        cout<<",";
    }
}
cout<<" : integer;"<<endl;
cout<<"begin"<<endl;
cout<<tab<<"readln(";
for(int j=0;j<znaki.length();j++)
{
    cout<<znaki[j];
    if(znaki.length()-1!=j)
    {
        cout<<",";
    }
}
cout<<");"<<endl;
wypisz(znaki,mn,tab);
cout<<"end."<<endl;
}
return 0;
}
