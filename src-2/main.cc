#include "./model.hpp"
#include <vector>

// SUMMARY of women day:
// + AbilityResult - piece of shit which contains result of an ability execution and the entity
// snapshots
// + ability execution response system - each ability applying returns AbilityResult
// + AbilityResult can be used by UI to produce step-by-step animations and reproduce what has
// happened
// + each dispatcher is wrapped by Entity.Apply or Map.ApplyAbility for auto-producing snapshots for
// entity_before and entity_after
// + void AnimationFunction(Entity entity_before, Entity entity_after, EventType event_type)
// + EventType describes what has happened with the Entity after the Ability applying

// + Map initilaizes by vector<Tile> where Tile is Tile with nullptr and actors and object with
// nullptrs same way
// + Map must assign itself to each provided Tile or Object or Actor
// + Map must provide way to get an entity by "path" - sequence of "pointers" which discribes a path
// through Map objects tree
// + UI gets Map snapshot as initial data with generated path for each entity (startup)

// NEXT BIG THINGS:
// - Entity.path exists
// - Entity.GeneratePath realization
// - Map.GetEntity realization
// - Map.ApplyAbility realization
// - develop an example of game scene

int main() {
    EntityActive character1 = EntityFactoryActive::CreateWarrior();
    EntityActive character2 = EntityFactoryActive::CreateWarrior();
    EntityActive character3 = EntityFactoryActive::CreateWarrior();

    Entity obj1 = EntityFactory::CreateThing();
    Entity obj2 = EntityFactory::CreateThing();
    Entity obj3 = EntityFactory::CreateThing();
    Entity obj4 = EntityFactory::CreateThing();

    std::vector<Tile> tiles = {
        Tile(nullptr, {obj1}, {character1}), // 0:0
        Tile(nullptr, {}, {character2}),     // 0:1
        Tile(nullptr, {}, {}),               // 0:2
        Tile(nullptr, {}, {}),               // 1:0
        Tile(nullptr,
             {
                 obj2,
                 obj3,
             },
             {}),                            // 1:1
        Tile(nullptr, {}, {}),               // 1:2
        Tile(nullptr, {}, {}),               // 2:0
        Tile(nullptr, {}, {}),               // 2:1
        Tile(nullptr, {}, {}),               // 2:2
        Tile(nullptr, {}, {}),               // 3:0
        Tile(nullptr, {obj4}, {character3}), // 3:1
        Tile(nullptr, {}, {}),               // 3:2
        Tile(nullptr, {}, {}),               // 4:0
        Tile(nullptr, {}, {}),               // 4:1
        Tile(nullptr, {}, {}),               // 4:2
    };

    Map world_map(tiles, 5, 3);

    // world_map.ApplyAbility();
}