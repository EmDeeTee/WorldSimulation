#ifndef LIMB_H
#define LIMB_H

#include <iostream>
#include <list>

class Limb {
public:
	Limb(std::string forBreed, std::string name, int hp);

	static std::list<Limb> AllLimbs;

	std::string ForBreed;
	std::string Name;
	int HP;
};

#endif
