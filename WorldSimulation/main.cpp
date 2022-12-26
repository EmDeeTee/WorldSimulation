#include <iostream>
#include <filesystem>
#include "Creature.h"
#include "Globals.h"
#include "Config.h"
#include "World.h"

#include <conio.h>

using std::cin; using std::cin;
using std::cout; using std::cout;

int main() {
    cout << "Welcome, hopefully Michau.\n";
    cout << "Current path is " << Globals::WorkingDirectory << '\n';

    ReadConfigFile();
    Creature::ReadCreaturesFile();

    cout << "Choose a name for the new World: ";
    std::string worldName; cin >> worldName;
    Globals::CurrentWorld = World(worldName);
    
    Globals::ShowMenu();
}
