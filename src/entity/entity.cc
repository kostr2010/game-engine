#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <vector>

#include "entity.hpp"

//====================
// METHODS IMPLEMENTATION

//===================
// coordinates

Coordinates::Coordinates(int x, int y) {
    x_ = x;
    y_ = y;
}

int Coordinates::GetX() {
    return x_;
}

int Coordinates::GetY() {
    return y_;
}

void Coordinates::SetCoordinates(int x_new, int y_new) {
    x_ = x_new;
    y_ = y_new;
}

//====================
// entity

Entity::Entity(Entity* parent, std::vector<Ability> abilities, std::vector<Entity> subentities, Coordinates coordinates) {
    subentities_ = subentities;
    coordinates_ = coordinates_;
    parent_      = parent;

    for (const auto& ability : abilities)
        abilities_[ability.kind_] = ability;
}

void Entity::Apply(AbilityKind kind, Entity& target) {
    if (abilities_.count(kind) != 0)
        dict_ability_dispatcher[kind](*this, target);

    return;
}

int Entity::GetSubEntitiesCount() {
    if (abilities_.count(CanContain) == 0)
        return 0;
    else
        return subentities_.size();
}

void Entity::AddSubentity(std::vector<Entity> items) {
    if (abilities_.count(CanContain) == 0)
        return;

    for (const Entity& item : items) {
        bool can_fit       = subentities_.size() < abilities_[CanContain].GetStateValue(ContainCapacity);
        int  can_be_picked = item.abilities_.count(CanBePicked);

        if (can_fit && can_be_picked != 0)
            subentities_.push_back(item);
        else if (!can_fit)
            break;
    }

    return;
}

void Entity::RemoveSubentity(size_t index) {
    if (abilities_.count(CanContain) == 0)
        return;

    if (index < subentities_.size())
        subentities_.erase(subentities_.begin() + index);

    return;
}

Entity Entity::GetSubentity(size_t index) {
    return (index < GetSubEntitiesCount()) ? (subentities_[index]) : throw std::string("hell yeah (20)");
}

std::ostream& operator<<(std::ostream& stream, Entity entity) {
    for (const auto& ability : entity.abilities_)
        stream << "AbilityKind - " << ability.first << ", Ability:" << ability.second << std::endl;

    return stream;
}

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

    return Entity(parent, {ability_die, ability_kick, ability_pick, ability_loot, ability_contain, ability_hack, ability_move});
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

    return Entity(parent, {ability_die, ability_contain});
}

/*
Entity EntityFactory::CreateMimic() {

}
*/

Entity EntityFactory::CreateFood(Entity* parent) {
    Ability ability_be_picked = AbilityFactory::CreateAbilityBePicked();

    return Entity(parent, {ability_be_picked});
}

Entity EntityFactory::CreateTile(Entity* parent) {
    // for now tile can contain up to 1 entity (may be changed)
    Ability ability_contain = AbilityFactory::CreateAbilityContain(1);

    return Entity(parent, {ability_contain});
}

Entity EntityFactory::CreateMap(size_t width, size_t height) {
    std::vector<Entity> tiles;
    tiles.reserve(height * width);

    Entity world_map(nullptr, {}, tiles);

    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            tiles[y * width + x] = CreateTile(&world_map);

    tiles.shrink_to_fit();

    return world_map;
}

//====================
// entity controller

// Entity EntityController::GetSubentityMap(Entity world_map, size_t x, size_t y) {
//     return world_map.GetSubentity()
// }