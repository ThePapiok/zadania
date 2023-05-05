#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;
struct Druzyny
{
    string nazwa_druzyny;
    int ilosc_punktow=0;
    int ilosc_meczy=0;
    int ilosc_wygranych_meczow=0;
    int ilosc_zremisowanych_meczow=0;
    int ilosc_przegranych_meczow=0;
    int ilosc_strzelonych_bramek=0;
    int ilosc_straconych_bramek=0;
};


bool jak(Druzyny D1,Druzyny D2)
{
    string Druzyna1,Druzyna2;
    if(D1.ilosc_punktow!=D2.ilosc_punktow)
    {
        return (D1.ilosc_punktow>D2.ilosc_punktow);
    }
    if(D1.ilosc_wygranych_meczow!=D2.ilosc_wygranych_meczow)
    {
        return (D1.ilosc_wygranych_meczow>D2.ilosc_wygranych_meczow);
    }
    if(D1.ilosc_strzelonych_bramek-D1.ilosc_straconych_bramek!=D2.ilosc_strzelonych_bramek-D2.ilosc_straconych_bramek)
    {
        return (D1.ilosc_strzelonych_bramek-D1.ilosc_straconych_bramek>D2.ilosc_strzelonych_bramek-D2.ilosc_straconych_bramek);
    }
    if(D1.ilosc_strzelonych_bramek!=D2.ilosc_strzelonych_bramek)
    {
        return (D1.ilosc_strzelonych_bramek>D2.ilosc_strzelonych_bramek);
    }
    if(D1.ilosc_meczy!=D2.ilosc_meczy)
    {
        return (D1.ilosc_meczy<D2.ilosc_meczy);
    }
        Druzyna1=D1.nazwa_druzyny;
        Druzyna2=D2.nazwa_druzyny;
        transform(Druzyna1.begin(),Druzyna1.end(),Druzyna1.begin(),::tolower);
        transform(Druzyna2.begin(),Druzyna2.end(),Druzyna2.begin(),::tolower);
        return(Druzyna1<Druzyna2);
}


int main()
{
    int N,T,G,il2,il1,warunek,pkt_wartosc[2];
    string linia,druzyna[2],pkt[2],nazwa_turnieju;
    cin>>N;
    cin.ignore();
    for(int i=0;i<N;i++)
    {
        getline(cin,nazwa_turnieju);
        cin>>T;
        cin.ignore();
        Druzyny D[T];
        for(int j=0;j<T;j++)
        {
            getline(cin,linia);
            D[j].nazwa_druzyny=linia;
        }
        cin>>G;
        cin.ignore();
        for(int j=0;j<G;j++)
        {
            getline(cin,linia);
            druzyna[0]="";
            druzyna[1]="";
            il2=0;
            il1=0;
            pkt[0]="";
            pkt[1]="";
            for(int k=0;k<linia.length();k++)
            {
                if(linia[k]=='#')
                {
                    il2++;
                }
                else if(linia[k]=='@')
                {
                    il1++;
                }
                else
                {
                    if(il2==0)
                    {
                        druzyna[0]=druzyna[0]+linia[k];
                    }
                    else if(il2==1)
                    {
                        if(il1==0)
                        {
                            pkt[0]=pkt[0]+linia[k];
                        }
                        else
                        {
                            pkt[1]=pkt[1]+linia[k];
                        }
                    }
                    else
                    {
                        druzyna[1]=druzyna[1]+linia[k];
                    }

                }
            }
            for(int k=0;k<=1;k++)
            {
                pkt_wartosc[k]=atoi(pkt[k].c_str());
            }
            if(pkt_wartosc[0]>pkt_wartosc[1])
            {
                warunek=1;
            }
            else if(pkt_wartosc[0]<pkt_wartosc[1])
            {
                warunek=2;
            }
            else
            {
                warunek=0;
            }
            for(int k=0;k<T;k++)
            {
                for(int l=0;l<=1;l++)
                {
                    if((D[k].nazwa_druzyny)==druzyna[l])
                    {
                        D[k].ilosc_meczy++;
                        D[k].ilosc_strzelonych_bramek+=pkt_wartosc[l];
                        if(l+1==2)
                        {
                            D[k].ilosc_straconych_bramek+=pkt_wartosc[0];
                        }
                        else
                        {
                            D[k].ilosc_straconych_bramek+=pkt_wartosc[1];
                        }
                        if(warunek==0)
                        {
                            D[k].ilosc_zremisowanych_meczow++;
                            D[k].ilosc_punktow++;
                        }
                        else
                        {
                            if(l==warunek-1)
                            {
                                D[k].ilosc_wygranych_meczow++;
                                D[k].ilosc_punktow+=3;
                            }
                            else
                            {
                                D[k].ilosc_przegranych_meczow++;
                            }
                        }
                    }
                }
            }

        }
        sort(D,D+T,jak);
        cout<<nazwa_turnieju<<endl;
        for(int k=0;k<T;k++)
        {
            cout<<k+1<<") "<<D[k].nazwa_druzyny<<" "<<D[k].ilosc_punktow<<"p, "<<D[k].ilosc_meczy<<"g ("<<D[k].ilosc_wygranych_meczow<<"-"<<D[k].ilosc_zremisowanych_meczow<<"-"<<D[k].ilosc_przegranych_meczow<<"), "<<D[k].ilosc_strzelonych_bramek-D[k].ilosc_straconych_bramek<<"gd ("<<D[k].ilosc_strzelonych_bramek<<"-"<<D[k].ilosc_straconych_bramek<<")"<<endl;
        }
        if(i!=N-1)
        {
            cout<<endl;
        }
    }
    return 0;
}
