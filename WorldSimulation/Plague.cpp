#include <string>
#include "Plague.h"
#include "Config.h"
#include "Creature.h"
#include "Globals.h"

Plague::Plague(std::string name, int severity) {
	this->Severity = severity;
	this->Name = name;
}

void Plague::Start() {
	if (IsVerbose()) std::cout << "A plague has started! Every creature with HP below " + std::to_string(this->Severity) + " Will die\n";

	for (Creature& c : Globals::CurrentWorld.WorldCreatures) {
		if (c.HP < this->Severity) {
			Globals::CurrentWorld.RemoveCreature(c);
		}
	}
}
