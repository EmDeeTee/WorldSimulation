#include <fstream>
#include <string>
#include "Saver.h"
#include "Globals.h"

void Saver::SaveWorld() {
	std::ofstream file(Globals::CurrentWorld.WorldName + ".world");
}
