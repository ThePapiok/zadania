#include "Smok.h"

void Smok::zjedz(Owca * o)
{
	zjedzona_siarka += o->siarka;
	cout<<"Zjadlem juz: "<<zjedzona_siarka<<endl;
}



Smok::Smok()
{
	zjedzona_siarka=0;
	cout<<"[Smok] Jestem zly i glodny smok"<<endl;
}

void Smok::zostaw(Mieszkaniec *m)
{
	cout<<"[Smok] Milcz slabeuszu!"<<endl;
}

void Smok::pomoc(Krol *k)
{
	cout<<"[Smok] Twoje wojsko nic mi nie zrobi"<<endl;
}