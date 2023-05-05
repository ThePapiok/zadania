#include <iostream>
#include "Smok.h"
using namespace std;

#ifndef KROL_H
#define KROL_H

class Mieszkaniec;

class Krol
{	
public:
	Krol();
	void pomoc(Mieszkaniec *m,Smok *s);
	
};
#endif