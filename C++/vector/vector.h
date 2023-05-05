#pragma once

using namespace std;

class Vector
{
	int *tab;
	int rozmiar=0;
	public:
	void init(int n);
	void init(Vector *v);
    void set_value(int index,int value);
    int get_value(int index);
    void append(int value);
    void free();
	Vector &operator<<(int value);
	int &operator[](int index);
    friend ostream& operator<<(ostream& s, const Vector & v);
};

void Vector::init(int n)
{
	tab=new int [n];
	rozmiar=n;
	for(int i=0;i<n;i++)
	{
		tab[i]=0;
	}
}

void Vector::init(Vector *v)
{
    rozmiar=v->rozmiar;
	tab=new int [rozmiar];
	for(int i=0;i<rozmiar;i++)
	{
		tab[i]=v->tab[i];
	}
}

void Vector::set_value(int index,int value)
{
	tab[index]=value;
}

int Vector::get_value(int index)
{
	return tab[index];
}

void Vector::append(int value)
{
	int *temp=tab;
	rozmiar++;
	tab=new int[rozmiar];
	for(int i=0;i<rozmiar-1;i++)
	{
		tab[i]=temp[i];
	}
	tab[rozmiar-1]=value;
	delete []temp;
}

void Vector::free()
{
	delete []tab;
	rozmiar=0;
}

Vector& Vector::operator<<(int value)
{
    append(value);
    return *this;
}

ostream& operator<<(ostream& s, const Vector & v)
    {
        for (int i=0;i<v.rozmiar;i++)
        {
            s<<v.tab[i]<<" ";
        }
		return s;
    }


int &Vector::operator[](int index)
{
    return tab[index];
}

