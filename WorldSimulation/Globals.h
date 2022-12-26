#ifndef GLOBALS_H
#define GLOBALS_H
#include "World.h"
#include <iostream>

#include <conio.h> // WINDOWS

using std::cin; using std::cin;
using std::cout; using std::cout;

class Globals {
public:
	static void ShowMenu();
	static int GenerateRandomInt(int max);
	static World CurrentWorld;
	static std::filesystem::path WorkingDirectory;
};


#endif
