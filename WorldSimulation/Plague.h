#ifndef PLAGUE_H
#define PLAGUE_H

#include "Disaster.h"

class Plague : public Disaster {
public:
	Plague(std::string name, int severity);

	void Start();
};

#endif 

