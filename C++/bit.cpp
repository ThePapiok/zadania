#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

void binarnie(int a);




int main()
{
    int a=175,b,n,l,c;
    bool program=true;
    do
    {
        cout<<"dziesiatkowy = "<<a<<endl;
        binarnie(a);
        cout<<"szesnastkowy = 0x"<<uppercase<<hex<<a<<dec<<endl<<endl;
        cout<<"1. zamien n-ty bit na 1"<<endl;
        cout<<"2. zamien n-ty bit na 0"<<endl;
        cout<<"3. wyjdz z programu"<<endl<<": ";
        cin>>b;
        if(b==1||b==2)
        {
            cout<<"podaj n-ty bit: ";
            cin>>n;
        }
        switch(b)
        {
            case 1:
            {
                a=a|(1<<n);
                break;
            }
            case 2:
            {
                a=a&(~(1<<n));
                break;
            }
            case 3:
            {
                program=0;
                break;
            }

        }
    }
    while(program);
    return 0;
}

void binarnie(int a)
{
    cout<<"dwojkowy = ";
    string bin="";
    while(a!=0)
    {
        bin+=to_string(a%2);
        a=a/2;
    }
    for(int i=bin.length()-1;i>=0;i--)
    {
        cout<<bin[i];
    }
    cout<<endl;
}

