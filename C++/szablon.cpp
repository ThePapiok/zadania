#include <iostream>
#include <array>
using namespace std;

template <typename T,size_t N,size_t M>
class VecN
{
	public:
	array<T,N> wektor;
	void setvalue()
	{
	    T wartosc;
		for(int i=0;i<N;i++)
		{
			cout<<"Wartosc ["<<i<<"] : ";
			cin>>wartosc;
			wektor[i]=wartosc;
		}
	}
	VecN operator*(T value)
	{
		VecN<T,N,M> temp;
		for(int i=0;i<N;i++)
		{
			temp.wektor[i]=wektor[i]*value;
		}
		return temp;
	}
	VecN operator+(VecN b)
	{
		VecN<T,N,M> temp;
		for(int i=0;i<N;i++)
		{
			temp.wektor[i]=wektor[i]+b.wektor[i];
		}
		return temp;
	}
	VecN operator-(VecN b)
	{
		VecN<T,N,M> temp;
		for(int i=0;i<N;i++)
		{
			temp.wektor[i]=wektor[i]-b.wektor[i];
		}
		return temp;
	}
	int dot(VecN b)
	{
		T iloczyn=0;
		for(int i=0;i<N;i++)
		{
			iloczyn+=wektor[i]*b.wektor[i];
		}
		return iloczyn;
	}
	VecN cross(VecN b)
	{
		VecN<T,N,M> temp;
		if(N!=3)
		{
			cout<<"Iloczyn wektorowy jest dostepny tylko dla wektorów 3-wymiarowych"<<endl;
		}
		else
		{
			temp.wektor[0]=wektor[1]*b.wektor[2]-wektor[2]*b.wektor[1];
			temp.wektor[1]=wektor[2]*b.wektor[0]-wektor[0]*b.wektor[2];
			temp.wektor[2]=wektor[0]*b.wektor[1]-wektor[1]*b.wektor[0];
		}
		return temp;
	}
	void average(array<VecN<T,N,M>,M> b)
	{
	    for(int i=0;i<N;i++)
        {
            for(int j=0;j<M;j++)
            {
                if(j==0)
                {
                    wektor[i]=b[j].wektor[i];
                }
                else
                {
                    wektor[i]=wektor[i]+b[j].wektor[i];
                }
            }
            wektor[i]/=M;
        }
	}
	void print()
	{
	    cout<<endl;
	    for(int i=0;i<N;i++)
        {
            cout<<wektor[i]<<endl;
        }
	}
};




int main()
{
	VecN<float,3,3> v,w,u;
    cout<<"wektor v: "<<endl;
	v.setvalue();
    v.print();
    cout<<"wektor w: "<<endl;
	w.setvalue();
    w.print();
	v=v*3;
    v.print();
	u=v+w;
	u.print();
	u=v-w;
	u.print();
    cout<<v.dot(w)<<" - iloczyn skalarny"<<endl;
	u=v.cross(w);
	u.print();
    array<VecN<float,3,3>,3> tab_wekt={u,v,w};
	u.average(tab_wekt);
	u.print();
	cin.ignore();
    cin.get();
    return 0;
}
