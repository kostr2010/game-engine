#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

// #include "engine-constants.hpp"
#include "engine-types.hpp"

using namespace std;

int main() {
    Entity world_map = EntityFactory::CreateMap(10, 10);

    // Entity ch1   = EntityFactory::CreateWarrior();
    // Entity ch2   = EntityFactory::CreateWarrior();
    // Entity chest = EntityFactory::CreateChest(10, 1);
    // Entity food  = EntityFactory::CreateFood();

    // chest.AddSubentity({food, food});
    // cout << "chest with food:\n" << chest << endl;
    // cout << "chest size:" << chest.GetSubEntitiesCount() << endl;

    // ch1.Apply(CanPick, food);
    // cout << "inventory size:" << ch1.GetSubEntitiesCount() << endl;

    // ch1.Apply(CanLoot, chest);
    // cout << "inventory size:" << ch1.GetSubEntitiesCount() << endl;
    // cout << "chest size:" << chest.GetSubEntitiesCount() << endl;

    // ch1.Apply(CanKick, ch2);

    // cout << "ch2: \n" << ch2;
}
