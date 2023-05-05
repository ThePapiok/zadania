#include <iostream>
#include <stack>
#include <queue>

using namespace std;


int main()
{
    int n,t,x,licznik;
    int wartosci[3];
    bool jest[3];
    while(cin>>n)
    {
        stack<int> stos;
        queue<int> kolejka;
        priority_queue<int> kopiec_maks;
        jest[0]=1;
        jest[1]=1;
        jest[2]=1;
        for(int i=1;i<=n;i++)
        {
            cin>>t>>x;
            if(t==1)
            {
              stos.push(x);
              kolejka.push(x);
              kopiec_maks.push(x);
            }
            else
            {
                if(stos.empty()==false)
                {
                    wartosci[0]=stos.top();
                    wartosci[1]=kolejka.front();
                    wartosci[2]=kopiec_maks.top();
                    for(int j=0;j<=2;j++)
                    {
                        if(wartosci[j]!=x)
                        {
                            jest[j]=0;
                        }
                    }
                    stos.pop();
                    kolejka.pop();
                    kopiec_maks.pop();
                }
                else
                {
                    jest[0]=0;
                    jest[1]=0;
                    jest[2]=0;
                }

                }
        }
        int il_jed=0,index;
        if(jest[0]==jest[1]&&jest[0]==jest[2]&&jest[0]==0)
        {
            cout<<"impossible"<<endl;
        }
        else
        {
            for(int i=0;i<=2;i++)
            {
                if(jest[i]==1)
                {
                    il_jed++;
                    index=i;
                }
            }
            if(il_jed>1)
            {
                cout<<"not sure"<<endl;
            }
            else
            {
                if(index==0)
                {
                    cout<<"stack"<<endl;
                }
                else if(index==1)
                {
                    cout<<"queue"<<endl;
                }
                else
                {
                    cout<<"priority queue"<<endl;
                }
            }
        }
    }
return 0;
}

