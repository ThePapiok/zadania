#include <iostream>
#include <queue>

using namespace std;

void zmiana_kierunku_statku(string &strona_statku, int &ilosc_aut);
void statek(int m,queue <int> &lewa_strona,queue <int> &prawa_strona, int czasy[],int n,int t, string kolejka[]);
void czekaj_za_autem(queue <int> &lewa_strona,queue <int> &prawa_strona,int &czas,bool &czekaj);


int main()
{
    int c,n,t,m,input_czas,tab[2];
    string input_strona;
    bool zmiana_kierunku;
    cin>>c;
    for(int i=1;i<=c;i++)
    {
        cin>>n>>t>>m;
        tab[1]=-1;
        queue<int> lewa_strona;
        queue<int> prawa_strona;
        string *kolejka=new string[m];
        int *czasy=new int[m];
        for(int j=0;j<=m-1;j++)
        {
            czasy[j]=-1;
        }
        for(int j=0;j<=m-1;j++)
        {
            cin>>input_czas>>input_strona;
            if(input_strona=="left")
            {
                lewa_strona.push(input_czas);
            }
            else
            {
                prawa_strona.push(input_czas);
            }
            kolejka[j]=input_strona;
        }
        statek(m,lewa_strona,prawa_strona,czasy,n,t,kolejka);
        for(int j=0;j<=m-1;j++)
        {
            cout<<czasy[j]<<endl;
        }
        cout<<endl;
        delete []czasy;
        delete []kolejka;
    }
    return 0;
}
void zmiana_kierunku_statku(string &strona_statku, int &ilosc_aut)
{

    if(strona_statku=="left")
    {
        strona_statku="right";
    }
    else
    {
        strona_statku="left";
    }
    ilosc_aut=0;

}

void statek(int m,queue <int> &lewa_strona,queue <int> &prawa_strona, int czasy[],int n,int t, string kolejka[])
{
   bool czekaj,zmiana_kierunku;
   string strona_statku;
   int temp,czas,ilosc_aut,p=0;
   strona_statku="left";
   czas=0;
   ilosc_aut=0;
        do
        {
            zmiana_kierunku=0;
            do
            {
                temp=ilosc_aut;
                czekaj=0;
                if(ilosc_aut<n)
                {
                    if(strona_statku=="left")
                    {
                        if(lewa_strona.front()<=czas && lewa_strona.empty()==0)
                        {
                            for(int j=0;j<=m-1;j++)
                            {
                                if(kolejka[j]=="left"&&czasy[j]==-1)
                                {
                                    czasy[j]=czas+t;
                                    j=m-1;
                                }
                            }
                            lewa_strona.pop();
                            if(lewa_strona.empty()==0)
                            {
                                ilosc_aut++;
                            }
                            zmiana_kierunku=1;
                            p++;
                        }
                        else
                        {
                                if(prawa_strona.front()<=czas && prawa_strona.empty()==0)
                                {
                                    zmiana_kierunku=1;
                                }
                                else
                                {
                                    if(ilosc_aut==0)
                                    {
                                        czekaj_za_autem(lewa_strona,prawa_strona,czas,czekaj);
                                    }
                                }
                        }
                    }
                    else
                    {
                        if(prawa_strona.front()<=czas && prawa_strona.empty()==0)
                        {
                            for(int j=0;j<=m-1;j++)
                            {
                                if(kolejka[j]=="right"&&czasy[j]==-1)
                                {
                                    czasy[j]=czas+t;
                                    j=m-1;
                                }
                            }
                            prawa_strona.pop();
                            if(prawa_strona.empty()==0)
                            {
                                ilosc_aut++;
                            }
                            zmiana_kierunku=1;
                            p++;
                        }
                        else
                        {
                            if(lewa_strona.front()<=czas && lewa_strona.empty()==0)
                            {
                                zmiana_kierunku=1;
                            }
                            else
                            {
                                if(ilosc_aut==0)
                                {
                                    czekaj_za_autem(lewa_strona,prawa_strona,czas,czekaj);

                                }
                            }
                        }
                    }
                }
            }
            while(temp!=ilosc_aut);
            if(czekaj!=1)
            {
                czas=czas+t;
            }
            if(zmiana_kierunku)
            {
                zmiana_kierunku_statku(strona_statku,ilosc_aut);
            }
        }
        while(p<m);
}
void czekaj_za_autem(queue <int> &lewa_strona,queue <int> &prawa_strona,int &czas,bool &czekaj)
{
    if(lewa_strona.empty()==1)
    {
        czas=prawa_strona.front();
    }
    else if(prawa_strona.empty()==1)
    {
        czas=lewa_strona.front();
    }
    else
    {
        if(lewa_strona.front()>prawa_strona.front())
        {
            czas=prawa_strona.front();
        }
        else
        {
            czas=lewa_strona.front();
        }
    }
    czekaj=1;
}
