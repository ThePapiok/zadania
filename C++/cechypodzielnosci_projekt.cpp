#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
using namespace std;


bool ost_1(string x, int dl, string l);
bool cecha_pot2(string x,int dl,string pot2,int il2);
bool ost_3(string x,int dl,string l);
bool cecha_pot5(string x,int dl,string pot5,int il5);
bool ost_7(string x,int dl,string l);
bool ost_9(string x,int dl, string l);
string cecha(string x,int dl,string mn,string l);
string dod(string a,string b);
string dziel(string a, string b, bool kt);
string od(string a,string b);
string mno(string a,string b);
string pot2i5(int &il_t,string pot, string pom2, vector<string> &pot_2, vector<string> &pot_5);
void kwiekszy(string &a,string &b);
void wzg_pierw(string pom2,vector<string> &liczby_war);




int main()
{
    string x,sprawdz,pom2,cyfra,test;
    int dl,il_t;
    bool j_pot,j_podz;
    vector<string> liczby_war;
    vector<bool> warunki;
    vector<string> pot_2;
    vector<string> pot_5;
    pot_2.push_back("2");
    pot_5.push_back("5");
    do
    {
        system("cls");
        cout<<"[0] - cofnij/zamknij program"<<endl;
        cout<<"Liczba: ";
        cin>>x;
        if(x!="0")
        {
            dl=x.length();
            do
            {
                cout<<": ";
                cin>>sprawdz;
                liczby_war.clear();
                warunki.clear();
                if(sprawdz!="0")
                {

                    liczby_war.push_back(sprawdz);
                    if(sprawdz=="1")
                    {
                        warunki.push_back(true);
                    }
                    else
                    {

						for(size_t o=0;o<=liczby_war.size()-1;o++)
						{
							pom2=liczby_war[o];
							cyfra=pom2[pom2.length()-1];
							if(cyfra=="1")
							{
								warunki.push_back(ost_1(x, dl, pom2));
							}
							else if(cyfra=="3")
							{
								warunki.push_back(ost_3(x, dl, pom2));
							}
							else if(cyfra=="7")
							{
								warunki.push_back(ost_7(x, dl, pom2));
							}
							else if(cyfra=="9")
							{
								warunki.push_back(ost_9(x, dl, pom2));
							}
							else
							{
                                j_pot=false;
                                il_t=0;
                                test=pot2i5(il_t,"2",pom2,pot_2,pot_5);
								if(test==pom2)
								{
								warunki.push_back(cecha_pot2(x,dl,pom2,il_t));
								j_pot=true;
								}
								if(j_pot==false)
								{
                                    il_t=0;
                                    test=pot2i5(il_t,"5",pom2,pot_2,pot_5);
                                    if(test==pom2)
                                    {
                                        warunki.push_back(cecha_pot5(x,dl,pom2,il_t));
                                        j_pot=true;
                                    }
								}
								if(j_pot==false)
								{
									wzg_pierw(pom2,liczby_war);
								}
							}
						}
                    }
                    j_podz=true;
                    for(size_t i=0;i<warunki.size();i++)
                    {
                        if(warunki[i]==false)
                        {
                            j_podz=false;
                            break;
                        }
                    }
                    if(j_podz==1)
                    {
                        cout<<"- jest podzielna przez "<<sprawdz<<endl;
                    }
                    else
                    {
                        cout<<"- nie jest podzielna przez "<<sprawdz<<endl;
                    }
                }
            }
            while(sprawdz!="0");
        }
    }
    while(x!="0");
    system("cls");
    return 0;
}

string cecha(string x,int dl,string mn,string l)
{
    string pom=x,a,b,a1,a2,min_l,znak;
    int min_dl;
    bool dalej=true;
    min_l=x;
    min_dl=dl;
    do
    {
        znak=pom[dl-1];
        pom=pom.erase(dl-1,dl);
        a=mno(znak,mn);
        b=pom;
        pom=od(a,b);
        dl=pom.length();
        if(dl<min_dl)
        {
            min_dl=dl;
            min_l=pom;
        }
        else if(dl==min_dl)
        {
            for(int i=0;i<=dl-1;i++)
            {
                a1=pom[i];
                a2=min_l[i];
                if(atoi(a1.c_str())<atoi(a2.c_str()))
                {
                    min_dl=dl;
                    min_l=pom;
                    break;
                }
                else
                {
                    dalej=false;
                    break;
                }
            }
        }
        else
        {
            dalej=false;
        }
    }
    while(dalej==true);
    return min_l;
}

bool ost_1(string x, int dl, string l)
{
    string mn,pom;
    pom=l;
    mn=pom.erase(pom.length()-1);
    string liczba=cecha(x,dl,mn,l);
    if(dziel(liczba,l,0)=="0")
    {
        return 1;
    }
    else
    {
      return 0;
    }
}

bool cecha_pot2(string x,int dl,string pot2, int il2)
{
    char znak;
    string liczba="";
    for(int i=il2;i>=1;i--)
    {
        znak=x[dl-i];
        if(dl-i>=0)
        {
            liczba=liczba+znak;
        }
    }
    for(int i=0;i<liczba.length()-1;i++)
    {
        if(liczba[i]=='0')
        {
            liczba.erase(i,1);
            i--;
        }
        else
        {
            break;
        }
    }
    if(dziel(liczba,pot2,0)=="0")
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

bool ost_3(string x,int dl,string l)
{

    string mn,pom;
    pom=l;
    mn=mno("7",pom.erase(pom.length()-1,1));
    mn=dod(mn,"2");
    string liczba=cecha(x,dl,mn,l);
    if(dziel(liczba,l,0)=="0")
    {
        return 1;
    }
    else
    {
        return 0;
    }

}
bool cecha_pot5(string x,int dl,string pot5,int il5)
{
    char znak;
    string liczba="";
    for(int i=il5;i>=1;i--)
    {
        znak=x[dl-i];
        if(dl-i>=0)
        {
            liczba=liczba+znak;
        }
    }
    for(int i=0;i<liczba.length()-1;i++)
    {
        if(liczba[i]=='0')
        {
            liczba.erase(i,1);
            i--;
        }
        else
        {
            break;
        }
    }
    if(dziel(liczba,pot5,0)=="0")
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

bool ost_7(string x,int dl,string l)
{
    string mn,pom;
    pom=l;
    mn=mno("3",pom.erase(pom.length()-1,1));
    mn=dod(mn,"2");
    string liczba=cecha(x,dl,mn,l);
    if(dziel(liczba,l,0)=="0")
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
bool ost_9(string x,int dl,string l)
{
    string mn,pom;
    pom=l;
    mn=mno("9",pom.erase(pom.length()-1,1));
    mn=dod(mn,"8");
    string liczba=cecha(x,dl,mn,l);
    if(dziel(liczba,l,0)=="0")
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void kwiekszy(string &a,string &b)
{
        string pom;
        char a1,a2;
        if(a.length()<b.length())
        {
            pom=a;
            a=b;
            b=pom;
        }
        else if(a.length()==b.length())
        {
            for(int i=0;i<=a.length()-1;i++)
            {
                a1=a[i]-'0';
                a2=b[i]-'0';
                if(a1>a2)
                {
                    break;
                }
                else if(a1<a2)
                {
                    pom=a;
                    a=b;
                    b=pom;
                    break;
                }
            }
        }
}

string od(string a,string b)
{
        kwiekszy(a,b);
        int dl_a,dl_b,r=0;
        string liczba="",pom="";
        char cyfra_a,cyfra_b;
        dl_a=a.length();
        dl_b=b.length();
        for(int i=1;i<=dl_a;i++)
        {
            cyfra_a=a[dl_a-i]-'0'-r;
            if(cyfra_a==-1)
            {
                cyfra_a=9;
                r=1;
            }
            else
            {
                r=0;
            }
            cyfra_b=0;
            if(dl_b-i>=0)
            {
                cyfra_b=b[dl_b-i]-'0';
            }
            if(cyfra_a>cyfra_b)
            {
                pom=pom+to_string(cyfra_a-cyfra_b);
            }
            else
            {
                if(cyfra_a<cyfra_b)
                {
                    if(cyfra_a==0)
                    {
                        cyfra_a=10;
                        r=1;
                    }
                    else
                    {
                        cyfra_a=10+cyfra_a;
                        r=1;
                    }
                }
                pom=pom+to_string(cyfra_a-cyfra_b);
            }
        }
        dl_a=pom.length();
        for(int i=dl_a-1;i>=0;i--)
        {
            liczba=liczba+pom[i];
        }
        for(int i=0;i<liczba.length()-1;i++)
        {
            if(liczba[i]=='0')
            {
                liczba.erase(i,1);
                i--;
            }
            else
            {
                break;
            }
        }
        return liczba;
}

string dod(string a,string b)
{
    kwiekszy(a,b);
    string pom="",liczba="";
    int dl_a,dl_b,r=0;
    char cyfra_a,cyfra_b;
    dl_a=a.length();
    dl_b=b.length();
    for(int i=0;i<=dl_a-1;i++)
    {
        cyfra_b=0;
        cyfra_a=a[dl_a-1-i]-'0';
        if(dl_b-1-i>=0)
        cyfra_b=b[dl_b-1-i]-'0';
        if(cyfra_a+cyfra_b+r>9)
        {
            pom=pom+to_string((cyfra_a+cyfra_b+r)%10);
            r=(cyfra_a+cyfra_b+r)/10;
        }
        else
        {
            pom=pom+to_string((cyfra_a+cyfra_b+r)%10);
            r=0;
        }
    }
    if(r>0)
    {
        pom=pom+to_string(r);
        r=0;
    }
    dl_a=pom.length();
    for(int i=dl_a-1;i>=0;i--)
    {
       liczba=liczba+pom[i];
    }
    for(int i=0;i<liczba.length()-1;i++)
    {
        if(liczba[i]=='0')
        {
            liczba.erase(i,1);
            i--;
        }
        else
        {
            break;
        }
    }
    return liczba;
 }

 string mno(string a, string b)
 {
     string pom1="0",pom2="",pom3="";
     int dl_a,dl_b,dl_c,r=0,zera=-1;
     char cyfra_a,cyfra_b;
     dl_a=a.length();
     dl_b=b.length();
     for(int i=dl_a-1;i>=0;i--)
     {
         zera++;
         cyfra_a=a[i]-'0';
         pom2="";
         pom3="";
         for(int j=dl_b-1;j>=0;j--)
         {
             cyfra_b=b[j]-'0';
             if((cyfra_a*cyfra_b)+r>9)
             {
                 pom2=pom2+to_string(((cyfra_a*cyfra_b)+r)%10);
                 r=((cyfra_a*cyfra_b)+r)/10;
             }
             else
             {
                 pom2=pom2+to_string(((cyfra_a*cyfra_b)+r)%10);
                 r=0;
             }
         }
         if(r>0)
         {
             pom2=pom2+to_string(r);
             r=0;
         }
         dl_c=pom2.length();
         for(int k=dl_c-1;k>=0;k--)
         {
             pom3=pom3+pom2[k];
         }
         for(int k=0;k<pom3.length()-1;k++)
         {
            if(pom3[k]=='0')
            {
                pom3.erase(k,1);
                k--;
            }
            else
            {
                break;
            }
         }
         for(int k=1;k<=zera;k++)
         {
             pom3=pom3+"0";
         }
         pom1=dod(pom3,pom1);


     }
     return pom1;
 }

string dziel(string a, string b, bool kt)
{
    string pom,pom2,pom1,dz="";
    int dl_a,cyfra_a,cyfra_b,mn=0;
    bool jest,mozna,pierw=true;
    dl_a=a.length();
    for(int i=0;i<=dl_a-1;i++)
    {
        pom=pom+a[i];
        for(int j=0;j<pom.length()-1;j++)
        {
            if(pom[j]=='0')
            {
                pom.erase(j,1);
                j--;
            }
            else
            {
                j=pom.length();
            }
        }
        jest=false;
        if(pom.length()>b.length())
        {
            jest=true;
        }
        else if(pom==b)
        {
            jest=true;
        }
        else if(pom.length()==b.length())
        {
            for(int j=0;j<=pom.length()-1;j++)
            {
                cyfra_a=pom[j]-'0';
                cyfra_b=b[j]-'0';
                if(cyfra_a>cyfra_b)
                {
                    jest=true;
                    break;

                }
                else if(cyfra_a<cyfra_b)
                {
                    break;
                }
            }
        }
        if(jest==true)
        {
            mn=0;
            pierw=false;
            pom2=pom;
            do
            {
                mozna=false;
                if(pom2.length()>b.length())
                {
                    mozna=true;

                }
                else if(pom2==b)
                {
                    mozna=true;
                }
                else if(pom2.length()==b.length())
                {
                    for(int j=0;j<=pom2.length()-1;j++)
                    {
                        cyfra_a=pom2[j]-'0';
                        cyfra_b=b[j]-'0';
                        if(cyfra_a>cyfra_b)
                        {
                            mozna=true;
                            break;

                        }
                        else if(cyfra_a<cyfra_b)
                        {
                            break;
                        }
                    }
                }
                if(mozna==true)
                {
                    mn++;
                    pom2=od(pom2,b);
                }
            }
            while(mozna==true);
            dz=dz+to_string(mn);
            pom1=mno(to_string(mn),b);
            pom=od(pom,pom1);
        }
        else
        {
            if(pierw==false)
            {
                dz=dz+"0";
            }
        }
    }
    if(kt==0)
    {
        return pom;
    }
    else if(kt==1)
    {
        return dz;
    }
}

string pot2i5(int &il_t,string pot, string pom2, vector<string> &pot_2, vector<string> &pot_5)
{
    string test="1";
    int cyfra_a,cyfra_b;
    bool j_pot_pom=false,jest=false;
    if(pot=="2")
    {
        for(size_t i=0;i<pot_2.size();i++)
        {
            il_t++;
            if(pot_2[i].length()>pom2.length())
            {
                test="0";
                jest=true;
                break;
            }
            if(pom2==pot_2[i])
            {
                test=pom2;
                jest=true;
                break;
            }
        }
    }
    else
    {
        for(size_t i=0;i<pot_5.size();i++)
        {
            il_t++;
            if(pot_5[i].length()>pom2.length())
            {
                test="0";
                jest=true;
                break;
            }
            if(pom2==pot_5[i])
            {
                test=pom2;
                jest=true;
                break;
            }
        }
    }
    if(jest==false)
    {
    do
    {
        if(pot=="2")
        {
           test=mno(pot,pot_2[pot_2.size()-1]);
           pot_2.push_back(test);
        }
        else
        {
            test=mno(pot,pot_5[pot_5.size()-1]);
            pot_5.push_back(test);
        }
        il_t++;
        if(test.length()>pom2.length())
        {
            j_pot_pom=true;
        }
        else if(test==pom2)
        {
            j_pot_pom=true;
        }
        else if(test.length()==pom2.length())
        {
            for(int i=0;i<=test.length()-1;i++)
            {
                cyfra_a=test[i]-'0';
                cyfra_b=pom2[i]-'0';
                if(cyfra_a>cyfra_b)
                {
                    j_pot_pom=true;
                    break;
                }
                if(cyfra_a<cyfra_b)
                {
                    break;
                }
            }
        }
    }
    while(j_pot_pom==false);
    }
    return test;
}

void wzg_pierw(string pom2 ,vector<string> &liczby_war)
{
    string test,a,b,pol_pom2,pom,pom3;
    bool j_pom;
    test="1";
    a="0";
    b="0";
    pol_pom2=dziel(pom2,"2",1);
    j_pom=false;
    do
    {
        test=dod(test,"1");
        pom3=dziel(pom2,test,1);
        if(dziel(pom2,test,0)=="0")
        {
            a=test;
            b=pom3;
        }
    while(b!="0")
    {
        a=dziel(a,b,0);
        pom=a;
        a=b;
        b=pom;
    }
    if(a=="1")
    {
        liczby_war.push_back(test);
        liczby_war.push_back(pom3);
        j_pom=true;
    }

    }
    while(j_pom==false);
}
