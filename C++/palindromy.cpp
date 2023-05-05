#include <iostream>
#include <vector>
using namespace std;
int minliter(string napis)
{
    string odw;
    int il;
    int dl = napis.length();
    for(int i=dl-1;i>=0;i--)
    {
        odw=odw+napis[i];
    }
    int tab[dl+1][dl+1];
    for(int i=0;i<dl+1;i++)
    {
        for(int j=0;j<dl+1;j++)
        {
            if(i==0||j==0)
            {
                tab[i][j]=0;
            }
            else if(napis[i-1]==odw[j-1])
            {
                tab[i][j]=1+tab[i-1][j-1];
            }
            else
            {
                tab[i][j]=max(tab[i-1][j],tab[i][j-1]);
            }
        }
    }
    il=dl-tab[dl][dl];
    if((il+dl)%2!=0)
    {
        il++;
    }
    return il;
}
vector<int> Manacher2(string s)
{
    s='$' + s + '&';
    vector<int> R;
    R.push_back(0);
    int i=1;
    int j=0;
    int k;
    while(i<=s.size()-1)
    {
        while(s[i-j]==s[i+j+1])
        {

            ++j;
        }
        R.push_back(j);
        k=1;
        while(R[i-k]!=R[i]-k&&k<=j)
        {
            R.push_back(min(R[i-k],R[i]-k));
            ++k;
        }
        j=max(j-k,0);
        i=i+k;

    }
    return R;
}

int main()
{
    string napis;
    int i,suma,il,dl,y,minroz=99999999;
    vector<int> NpPa;
    do
    {
    cin>>napis;
    suma=0;
    il=0;
    NpPa = Manacher2(napis);
    for(i=0;i<NpPa.size();++i)
    {
        suma=suma+NpPa[i];
    }
    dl=napis.length();
    il=minliter(napis);
    cout<<suma<<" "<<il<<endl;
    if(dl%2==0)
    {
       y=dl/2+1;
    }
    else
    {
       y=dl/2+2;
    }
    for(int i=0;i<=(dl/2)-1;i++)
    {
        for(int j=dl-1;j>=y-1;j--)
        {
            if(napis[i]==napis[j])
            {
                cout<<napis[i]<<" "<<napis[j];
                if(j-i<minroz)
                {
                    cout<<" "<<j-i<<endl;
                    minroz=j-i;
                }
            }
        }
    }
    cout<<minroz;

    }
    while(il!=0);
    return 0;
}
