#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

// #include "engine-constants.hpp"
#include "engine-types.hpp"

using namespace std;

int main() {
    Entity world_map = EntityFactory::CreateMapShell();
    EntityFactory::InitMap(&world_map, 10, 10);

    Entity ch1   = EntityFactory::CreateWarrior(world_map.GetSubentity(1));
    Entity ch2   = EntityFactory::CreateWarrior(world_map.GetSubentity(2));
    Entity chest = EntityFactory::CreateChest(world_map.GetSubentity(3), 10, 1);
    Entity food  = EntityFactory::CreateFood(world_map.GetSubentity(4));

    chest.AddSubentity({food, food});
    cout << "chest with food:\n" << chest << endl;
    cout << "chest size:" << chest.GetSubEntitiesCount() << endl;

    ch1.Apply(CanPick, food);
    cout << "inventory size:" << ch1.GetSubEntitiesCount() << endl;

    ch1.Apply(CanLoot, chest);
    printf("%s: %d\n", "inventory size", ch1.GetSubEntitiesCount());
    printf("%s: %d\n", "chest size", chest.GetSubEntitiesCount());

    ch1.Apply(CanKick, ch2);

    cout << "ch2: \n" << ch2;
}
