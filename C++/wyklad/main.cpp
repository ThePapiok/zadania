#include <iostream>
#include "Smok.h"
#include "Owca.h"
#include "Mieszkaniec.h"

using namespace std;

int main()
{
	cout<<"[Narrator] Pewnego razu, za gorami, za lasami"<<endl;
	cout<<"[Narrator] bylo sobie pewne krolestwo."<<endl;
	cout<<"[Narrator] Jednak od pewnego momentu mialo pewien problem."<<endl;
	cout<<"[Narrator] Pojawil sie bardzo irytujacy smok."<<endl;
	Smok s=Smok();
	cout<<"[Narrator] Mieszkancy tego krolestwa byli bardzo zdesperwani."<<endl;
	Mieszkaniec m=Mieszkaniec();
	cout<<"[Narrator] Smok byl glodny i zjadal wszystkie zwierzeta,"<<endl;
	cout<<"[Narrator] ktore byly aktualnie na polu."<<endl;
	m.zostaw(&s)
	cout<<"[Narrator] Mieszkancy poszli o pomoc do krola."<<endl;
	Krol k=Krol();
	m.pomoc(&k);
	s.odp();
	Owca o1=Owca(15);
	Owca o2=Owca(25);
	cout<<"Pierwsza owca do smoka"<<endl;
	s.zjedz(&o1);
	cout<<"Druga owca do smoka"<<endl;
	s.zjedz(&o2);
}