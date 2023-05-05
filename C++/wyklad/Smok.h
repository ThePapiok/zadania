#include <iostream>
#include "Owca.h"

using namespace std;

#ifndef SMOK_H
#define SMOK_H

class Mieszkaniec;

class Smok
{
private:
	int zjedzona_siarka;
	
public:
	Smok();
	void zjedz(Owca *o);
	void zostaw(Mieszkaniec *m);
	void pomoc(Krol *k);
	
};
#endif