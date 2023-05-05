#include <iostream>
#include <cmath>
using namespace std;

bool pierw[101];

int main()
{
int N,sm;
int il[101],ilo;
for(int i=2;i<=sqrt(100);i++)
{
      sm=i+i;
      while(sm<=100)
      {
          pierw[sm]=1;
          sm=sm+i;
      }
}
do
{
  cin>>N;
  ilo=0;
  for(int i=2;i<=100;i++)
  {
      il[i]=0;
  }
  if(N!=0)
  {
      for(int i=N;i>=2;i--)
      {
        sm=i;
        do
        {
            for(int j=2;i<=100;j++)
            {
                if(pierw[j]==0&&sm%j==0)
                {
                    il[j]++;
                    sm=sm/j;
                    break;
                }
            }
        }
        while(sm!=1);
      }
      cout.width(3);
      cout<<right<<N<<"! =";
      for(int i=2;i<=100;i++)
      {
          if(il[i]>0)
          {
                if(ilo==15)
                {
                    cout<<endl<<"      ";
                }
                cout.width(3);
                cout<<right<<il[i];
                ilo++;
          }
      }
      cout<<endl;
  }
}
while(N!=0);
return 0;
}
