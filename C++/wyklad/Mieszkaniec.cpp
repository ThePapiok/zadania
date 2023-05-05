#include "Mieszkaniec.h"

void Mieszkaniec::zostaw(Smok *s)
{
	cout<<"[Mieszkaniec] "<<"Zostaw nas prosze"<<endl;
	s->zostaw(this);
}

void Mieszkaniec::pomoc(Krol *k)
{
	cout<<"[Mieszkaniec] "<<"Pomoz nam dobry krolu"<<endl;
	k->pomoc(this);
}

Mieszkaniec::Mieszkaniec()
{
	cout<<"[Mieszkaniec] "<<"Jestem taki bezbronny"<<endl;
}