#include "entity-factory.hpp"
#include "ability-factory.hpp"

#include "../main-classes/main-classes.hpp"

//====================
// METHODS IMPLEMENTATION

//====================
// entity factory

Entity EntityFactory::CreateWarrior(Entity* parent) {
    Ability ability_die     = AbilityFactory::CreateAbilityDie(10, 10);
    Ability ability_kick    = AbilityFactory::CreateAbilityKick(4);
    Ability ability_pick    = AbilityFactory::CreateAbilityPick();
    Ability ability_loot    = AbilityFactory::CreateAbilityLoot();
    Ability ability_contain = AbilityFactory::CreateAbilityContain(10);
    Ability ability_hack    = AbilityFactory::CreateAbilityHack(1);
    Ability ability_move    = AbilityFactory::CreateAbilityMove();

    return Entity(Warrior,
                  parent,
                  {ability_die, ability_kick, ability_pick, ability_loot, ability_contain, ability_hack, ability_move},
                  {},
                  parent->GetCoordinates());
}
/*
Entity EntityFactory::CreateMage() {

}

Entity EntityFactory::CreateCustom() {

}
*/

Entity EntityFactory::CreateChest(Entity* parent, size_t capacity, size_t init_lock_lvl) {
    Ability ability_contain   = AbilityFactory::CreateAbilityContain(capacity);
    Ability ability_die       = AbilityFactory::CreateAbilityDie(100, 100);
    Ability ability_be_locked = AbilityFactory::CreateAbilityBeLocked(init_lock_lvl);

    return Entity(Chest, parent, {ability_die, ability_contain}, {}, parent->GetCoordinates());
}

/*
Entity EntityFactory::CreateMimic() {

}
*/

Entity EntityFactory::CreateFood(Entity* parent) {
    Ability ability_be_picked = AbilityFactory::CreateAbilityBePicked();

    return Entity(Food, parent, {ability_be_picked}, {}, parent->GetCoordinates());
}

Entity EntityFactory::CreateTile(Entity* parent, Coordinates pos, int walkable_level) {
    // for now tile can contain up to 1 entity (may be changed)
    Ability ability_contain = AbilityFactory::CreateAbilityContain(1);

    return Entity(Tile, parent, {ability_contain}, {}, pos);
}

Entity EntityFactory::CreateMapShell() {
    Entity world_map(Map, nullptr);

    return world_map;
}

Entity EntityFactory::InitMap(Entity* mapShell, size_t width, size_t height) {
    std::vector<Entity> tiles;
    tiles.reserve(height * width);

    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            // tiles[y * width + x] = CreateTile(mapShell, {x, y}); // ???????????????
            tiles.push_back(CreateTile(mapShell, {x, y}, 0));

    tiles.shrink_to_fit();

    std::cout << "tiles.size(): " << tiles.size() << std::endl;
    mapShell->subentities_ = tiles;

    return *mapShell;
}
