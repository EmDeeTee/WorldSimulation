#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <list>
#include "GodConsole.h"
#include "Creature.h"
#include "Globals.h"
#include "Plague.h"
#include <random>

void GodConsole::ShowConsole() {
	cout << "\033[2J";
	cout << "Welcome to GodConsole. Powered by GoDLang\n";
	
	while (true) {
		cout << "GoD> ";
		std::string input;
		std::cin >> input;

		std::vector<std::string> array;
		std::stringstream ss(input);
		std::string tmp;
		while (std::getline(ss, tmp, ':')) {
			array.push_back(tmp);
		}
		if (array[0] == "q") {
			Globals::ShowMenu();
		}
		if (array[0] == "GetBreedPop" && array.size() > 1) {
			std::string breedName = array[1];
			__int64 pop = 0;
			for (Creature& it : Globals::CurrentWorld.WorldCreatures) {
				if (it.BreedName == breedName) {
					pop++;
				}
			}
			cout << "Total alive population of " + breedName + " is: " + std::to_string(pop) + "\n";
		}
		if (array[0] == "GetLimbs" && array.size() > 1) {
			for (auto& it : Limb::AllLimbs) {
				if (it.ForBreed == array[1]) {
					cout << it.Name + "\n";
					cout << "-	HP: " + std::to_string(it.HP) + "\n";
				}
			}
		}
		if (array[0] == "ListCreaturesBreed" && array.size() > 1) {
			for (auto& it : Globals::CurrentWorld.WorldCreatures) {
				if (it.BreedName != array[1]) return;
				std::string femaleYesNo = it.IsFemale ? "Yes\n" : "No\n";
				cout << it.Name + "\n";
				cout << "-	UUID: " + it.uuid + "\n";
				cout << "-	Age: " + std::to_string(it.Age) + "\n";
				cout << "-	HP: " + std::to_string(it.HP) + "\n";
				cout << "-	Female?: " + femaleYesNo;
			}
		}
		if (array[0] == "ListAllCreatures") {
			for (auto& it : Globals::CurrentWorld.WorldCreatures) {
				std::string femaleYesNo = it.IsFemale ? "Yes\n" : "No\n";
				cout << it.BreedName + "\n";
				cout << it.Name + "\n";
				cout << "-	UUID: " + it.uuid + "\n";
				cout << "-	Age: " + std::to_string(it.Age) + "\n";
				cout << "-	HP: " + std::to_string(it.HP) + "\n";
				cout << "-	Female?: " + femaleYesNo;
			}
		}
		if (array[0] == "Kill" && array.size() > 1) {
			for (auto& it : Globals::CurrentWorld.WorldCreatures) {
				if (it.uuid == array[1]) {
					Globals::CurrentWorld.RemoveCreature(Creature::Find(array[1]));
				}
			}
		}
		if (array[0] == "BreedInfo" && array.size() > 1) {
			for (auto& it : Creature::AllBreedNames) {
				cout << it + "\n";
				//cout << "-	Life expectancy: " + std::to_string(it.LifeExpectancy) + "\n";
			}
		}
		if (array[0] == "StartDisaster" && array.size() == 4) {
			if (array[1] == "Plague") {
				Globals::CurrentWorld.StartDisaster(Plague(array[2], std::stoi(array[3])));
			}
			else {
				cout << "Wrong disaster name\n";
			}
		}
		if (array[0] == "Enlighten" && array.size() > 1) {
			// Enlighten the creature, making it acknowledge, that it's in a simulation
			for (auto& it : Globals::CurrentWorld.WorldCreatures) {
				if (it.uuid == array[1]) {
					if (Globals::GenerateRandomInt(1) == 1) {
						Globals::CurrentWorld.RemoveCreature(Creature::Find(array[1]));
					}
				}
			}
		}
		if (array[0] == "Devastate" && array.size() > 1) {
			int howMuch = std::stoi(array[1]);

			Globals::CurrentWorld.Devastate(howMuch);
		}
	}
}
