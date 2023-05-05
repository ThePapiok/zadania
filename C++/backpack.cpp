#include <iostream>
#include <vector>

using namespace std;

#define weight_of_backpack 10
#define price_of_backpack 10

class Item
{
	public:
	virtual string name()=0;
	virtual int weight()=0;
	virtual int price()=0;
	virtual void print()=0;
	virtual ~Item()
	{

	}

};

class Coin: public Item
{
    string name_of_item="moneta";
    int weight_of_item=1;
    int price_of_item=10;
    public:
    virtual string name()
    {
        return name_of_item;
    }
	virtual int weight()
	{
	    return weight_of_item;
	}
	virtual int price()
	{
	    return price_of_item;
	}
	virtual void print()
	{
	   cout<<name()<<" "<<weight()<<" "<<price()<<endl;
	}
	virtual ~Coin()
	{
        cout<<"delete Coin"<<endl;
	}
};

class Knife: public Item
{
    string name_of_item="noz kuchenny";
    int weight_of_item=10;
    int price_of_item=50;
    public:
    virtual string name()
    {
        return name_of_item;
    }
	virtual int weight()
	{
	    return weight_of_item;
	}
	virtual int price()
	{
	    return price_of_item;
	}
	virtual void print()
	{
	   cout<<name()<<" "<<weight()<<" "<<price()<<endl;
	}
	virtual ~Knife()
	{
		cout<<"delete Noz"<<endl;
	}
};

class FirstAid: public Item
{
	string name_of_item="apteczka";
    int weight_of_item=150;
    int price_of_item=100;
    public:
    virtual string name()
    {
        return name_of_item;
    }
	virtual int weight()
	{
	    return weight_of_item;
	}
	virtual int price()
	{
	    return price_of_item;
	}
	virtual void print()
	{
	   cout<<name()<<" "<<weight()<<" "<<price()<<endl;
	}
	virtual ~FirstAid()
	{
		cout<<"delete Apteczka"<<endl;
	}

};

class Backpack: public Item
{
	vector <Item*> items;
	int max_weight;
	public:
	Backpack(int n=2000)
	{
		max_weight=n;
	}
	int add(Item *it)
	{
	 	if(it->weight()+weight()-weight_of_backpack<=max_weight)
        {
            items.push_back(it);
            return items.size()-1;
        }
        else
        {
            return -1;
        }
	}
	size_t count()
	{
		return items.size();
	}
	void remove(int index)
	{
		delete items[index];
		items.erase(items.begin()+index);
	}
	Item * operator[](int index)
	{
	    return items[index];
	}
	virtual ~Backpack()
	{
		cout<<"delete Backpack"<<endl;
		int n=count();
		for(int i=0;i<n;i++)
		{
			delete items[i];
		}
		items.clear();
	}
	virtual string name() override
	{
	}
	virtual int weight() override
	{
		int n=count(),sum=0;
		for(int i=0;i<n;i++)
		{
			sum+=items[i]->weight();
		}
		sum+=weight_of_backpack;
		return sum;
	}
	virtual int price() override
	{
		int n=count(),sum=0;
		for(int i=0;i<n;i++)
		{
			sum+=items[i]->price();
		}
		sum+=price_of_backpack;
		return sum;
	}
	virtual void print() override
	{
		int n=count();
		for(int i=0;i<n;i++)
		{
			items[i]->print();
		}
	}

};


int main()
{
Backpack b(10);
cout<<b.add(new Coin)<<endl;
cout<<b.add(new Knife)<<endl;
b.print();
cout<<b.price()<<endl;
cout<<b.weight()<<endl;
b.remove(0);
cout<<b.add(new FirstAid)<<endl;
b.print();
cout<<b.price()<<endl;
cout<<b.weight()<<endl;
for(int i=0;i<b.count();i++)
{
  cout<<b[i]->name()<<": " <<b[i]->price()<<" "<<b[i]->weight()<<endl;
}
return 0;
}


