#include "Creature.h"
#include "Globals.h"

json Creature::Data;
std::string Creature::RawData;
std::list<std::string> Creature::AllBreedNames;
std::map<std::string, CreatureTemplate> Creature::CreatureTemplates;


void Creature::ReadCreaturesFile() {
    if (!fs::exists("creatures.json")) {
        cout << "[ERROR] CAN'T OPEN 'creatures.json'";
        getchar();
        exit(-1);
    }
    
    cout << "Reading creatures file...\n";
    std::ifstream configFile("creatures.json");
    json data = json::parse(configFile);
    Data = data;
    RawData = data.dump();

    for (auto &element : data.items()) {
        AllBreedNames.push_back(element.key());
        bool shouldCreateTemplate = false;
        if (CreatureTemplate::Templates.size() == 0) shouldCreateTemplate = true;
        for (auto& it : CreatureTemplate::Templates) {
            if (it.ForBreed != element.key()) {
                shouldCreateTemplate = true;
            }
            else {
                shouldCreateTemplate = false;
            }
        }
        if (shouldCreateTemplate) {
            int LifeExpectancy = Data[element.key()]["LifeExpectancy"];
            int baseHp = Data[element.key()]["HP"];
            int BreedSpeed = Data[element.key()]["BreedSpeed"];
            int BreedCooldown = Data[element.key()]["BreedCooldown"];
            int BreedAge = Data[element.key()]["BreedAge"];
            int MaxBreedAge = Data[element.key()]["MaxBreedAge"];
            int Violence = Data[element.key()]["Violence"];
            int Size = Data[element.key()]["Size"];

            //Get a random name from the "Names" array
            std::string Name = Data[element.key()]["Names"][Globals::GenerateRandomInt(Data[element.key()]["Names"].size() - 1)];

            CreatureTemplate::Templates.push_back(CreatureTemplate(element.key(), Name,
                baseHp, LifeExpectancy, BreedSpeed, BreedCooldown, BreedAge, MaxBreedAge, Violence,
                Size));
        }
    }


    try { // Limbs
        for (nlohmann::json::iterator it = data.begin(); it != data.end(); ++it) {
            std::string key = it.key();

            // Access the Limbs object of the current element
            auto& limbs = it.value()["Limbs"];

            // Access the values of the children of the Limbs object
            std::string name = limbs["Name"];
            int hp = limbs["HP"];

            Limb::AllLimbs.push_back(Limb(key, name, hp));
        }
    }
    catch (std::exception e) {
        cout << "Creature.cpp: Error while reading the 'creatures.json' file!\n";
    }
    
}

Creature Creature::CreateCreature(std::string name, int age, bool isFemale) {
    // Why did I made this?
    
    return Creature(name, age, isFemale);
}

Creature::Creature(std::string breedName, int age, bool isFemale) {
    this->BreedName = breedName;
    this->Age = age;
    this->IsFemale = isFemale;
}

Creature::Creature()
{
}

void Creature::Kill() {
    cout << "Killed: " + this->BreedName + "\n";
}

Creature Creature::Find(std::string uuid) {
    for (auto& it : Globals::CurrentWorld.WorldCreatures) {
        if (it.uuid == uuid) {
            return it;
        }
    }
}
