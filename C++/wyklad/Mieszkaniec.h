#include <iostream>
#include "Smok.h"

using namespace std;

#ifndef MIESZKANIEC_H
#define MIESZKANIEC_H
class Mieszkaniec
{
public:
	Mieszkaniec();
	void zostaw(Smok *s);
	void pomoc(Krol *k);

};
#endif