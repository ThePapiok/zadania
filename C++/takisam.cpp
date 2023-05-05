#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

void save_vector(vector<double> v,string plik);
vector <double> load_vector(string plik);


int main()
{
    vector <double> v;
    string plik;
    cout<<"Nazwa pliku: ";
    cin>>plik;
    srand(time(NULL));
    for(int i=1;i<=1000;i++)
    {
        v.push_back(rand()%1000000);
    }
    save_vector(v,plik);
    vector <double> w=load_vector(plik);
    if(v==w)
    {
        cout<<"taki sam"<<endl;
    }
    else
    {
        cout<<"nie jest taki sam"<<endl;
    }
}


void save_vector(vector<double> v,string plik)
{
    fstream save;
    size_t s=v.size();
    save.open(plik.c_str(),ios::binary | ios::out);
    save.write((char*)&s,sizeof(s));
    save.write((char*)v.data(),sizeof(v[0])*v.size());
    save.close();
}


vector <double> load_vector(string plik)
{
    fstream load;
    vector <double> p;
    size_t s;
    load.open(plik.c_str(),ios::binary | ios::in);
    load.read((char*)&s,sizeof(s));
    p.resize(s);
    load.read((char*)p.data(),s*sizeof(p[0]));
    load.close();
    return p;
}