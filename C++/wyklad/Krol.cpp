#include "Krol.h"
#include "Smok.h"

Krol::Krol()
{
	cout<<"[Krol] Jestem dobrym krolem"<<endl;
}

void Krol::pomoc(Mieszkaniec *m,Smok *s)
{
	cout<<"[Krol] Pomoge wam moi mieszkancy"<<endl;
	cout<<"[Krol] Wysle wojsko na niego"<<endl;
	s->pomoc(this);
}