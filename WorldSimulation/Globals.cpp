#include <filesystem>
#include <format>
#include <string>
#include <string_view>
#include "Globals.h"
#include "Creature.h"
#include "Matter.h"
#include "GodConsole.h"
#include "Saver.h"
#include <random>

World Globals::CurrentWorld;
std::filesystem::path Globals::WorkingDirectory = std::filesystem::current_path();

void Globals::ShowMenu() {
    cout << "s - Start simulation on current World\n";
    cout << "S - Progress the simulation by...\n";
    cout << "i - View current World statistics\n";
    cout << "a - Add matter to the current World\n";
    cout << "c - GoD Console\n";
    cout << "q - Quit\n";

    cout << "What do you want to do?\n";
    int i = 0;
    while (true) {
        char option = _getch(); // Windows only

        std::string creatureBreedName = "";
        int howManyTics = 0;
        int creatureAge = 0;
        bool isCreatureFemale = false;

        switch (option) {
        case 's':
            cout << std::string(100, '\n');
            CurrentWorld.StartSimulation();
            break;
        case 'S':
            cout << std::string(100, '\n');
            cout << "How many tics? ";
            cin >> howManyTics;
            CurrentWorld.StartSimulation(howManyTics);
            break;
        case 'q':
            Saver::SaveWorld();
            exit(0);
            break;
        case 'a':
            cout << "What would you like to add?\n";
            cout << "c - Creatures\n";
            cout << "q - Done\n";

            while (true) {
                option = _getch();
                if (option == 'q') Globals::ShowMenu();
                cout << "Creature breed name from creatures.json: ";
                cin >> creatureBreedName;
                cout << "Creature age: ";
                cin >> creatureAge;
                cout << "Is the creature female (0/1): ";
                cin >> isCreatureFemale;


                CurrentWorld.AddCreature(Creature(creatureBreedName, creatureAge, isCreatureFemale));
                cout << std::format("Added {} {} of age {}", creatureBreedName, isCreatureFemale ? "female" : "male", creatureAge) + "\n";
                cout << "'q' - Done\n";
            }
            break;
        case 'i':
            cout << "\033[2J";
            cout << "World Info\n=====================================\n";
            cout << "Alive creatures: " + std::to_string(CurrentWorld.WorldPopulation) + "\n";
            cout << "World devastation: " + std::to_string(CurrentWorld.GetDevastation()) + "%\n";

            cout << "\n\nDetalied Creatures Info\n=====================================\n";
            cout << "Breed breakdown: \n";
            for (auto const& [key, val] : CurrentWorld.BreedPopulation) {
                // val != 0 because there is a weird bug in the matrix, that overtime causes
                // something to leak into CurrentWorld.BreedPopulation and add an entry with
                // value of 0. I'll ignore it, I'm sure it's fine and it will have no
                // unforeseen consequences in the future
                if (val != 0) cout << key + "s: " + std::to_string(val) + "\n";
            }

            break;
        case 'c':
            GodConsole::ShowConsole();
            break;
        default:
            cout << "Unknown command\n";
            break;
        }
    }
}

int Globals::GenerateRandomInt(int max) {
    std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, max);
    return dist(generator);
}
