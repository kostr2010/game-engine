#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <vector>

#include "engine-constants.hpp"
#include "engine-types.hpp"

//====================
// METHODS IMPLEMENTATION

//====================
// ability

Ability::Ability() {
    return;
}

Ability::Ability(AbilityKind kind, std::map<AbilityState, int> init_state) {
    state_ = init_state;
    kind_  = kind;
}

int Ability::GetStateValue(AbilityState name) {
    return state_[name];
}

void Ability::SetStateValue(AbilityState name, int new_value) {
    state_[name] = new_value;
}

bool operator==(const Ability& left, const Ability& right) {
    return left.state_ == right.state_;
}

std::ostream& operator<<(std::ostream& stream, Ability ability) {
    stream << ability.kind_ << ": ";

    for (const auto& s : ability.state_)
        stream << s.second << " ";

    return stream;
}

//====================
// ability factory

Ability AbilityFactory::CreateAbilityDie(size_t hp_max, size_t hp_current) {
    Ability ability_die = Ability(CanDie, {{HpMax, hp_max}, {HpCurrent, hp_current}});

    return ability_die;
}

Ability AbilityFactory::CreateAbilityKick(size_t damage) {
    Ability ability_kick = Ability(CanKick, {{DamageAmount, damage}});

    return ability_kick;
}

Ability AbilityFactory::CreateAbilityPick() {
    Ability ability_pick = Ability(CanPick, {});

    return ability_pick;
}

Ability AbilityFactory::CreateAbilityLoot() {
    Ability ability_pick = Ability(CanLoot, {{SpotToLoot, 0}});

    return ability_pick;
}

Ability AbilityFactory::CreateAbilityBePicked() {
    Ability ability_be_picked = Ability(CanBePicked, {});

    return ability_be_picked;
}

Ability AbilityFactory::CreateAbilityContain(size_t capacity) {
    Ability ability_contain = Ability(CanContain, {{ContainCapacity, capacity}});

    return ability_contain;
}

Ability AbilityFactory::CreateAbilityMove() {
    Ability ability_move = Ability(CanMove, {});

    return ability_move;
}

Ability AbilityFactory::CreateAbilityHack(size_t hack_level) {
    Ability ability_hack = Ability(CanHack, {{HackLevel, hack_level}});

    return ability_hack;
}

Ability AbilityFactory::CreateAbilityBeLocked(size_t lock_level) {
    Ability ability_be_locked = Ability(CanBeLocked, {{LockLevel, lock_level}});

    return ability_be_locked;
}

Ability AbilityFactory::CreateAbilityBeMap(size_t width, size_t height) {
    Ability ability_be_map = Ability(IsMap, {{MapWidth, width}, {MapHeight, height}});
    return ability_be_map;
}

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

Entity::Entity(EntityKind kind, Entity* parent, std::vector<Ability> abilities, std::vector<Entity> subentities, Coordinates coordinates) {
    subentities_ = subentities;
    coordinates_ = coordinates_;
    parent_      = parent;
    kind_        = kind;

    id_ = sole::uuid1();

    if (parent != nullptr)
        parent->subentities_.push_back(*this); // Check if works

    for (const auto& ability : abilities)
        abilities_[ability.kind_] = ability;
}

void Entity::Apply(AbilityKind kind, Entity& target) {
    if (abilities_.count(kind) != 0)
        dict_ability_dispatcher[kind](*this, target);

    return;
}

Entity* Entity::GetParentTile() {
    if (parent_ == nullptr)
        throw std::string("no appropriate parent");

    if (parent_->kind_ == Tile)
        return parent_;
    else
        return parent_->GetParentTile();
}

int Entity::GetSubEntitiesCount() {
    return subentities_.size();
    // std::cout << "**" << std::endl;
    // if (abilities_.count(CanContain) == 0) {
    //     std::cout << "**_1" << std::endl;
    //     return 0;
    // } else {
    //     std::cout << "**_2" << std::endl;
    //     return subentities_.size();
    // }
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

Entity* Entity::GetSubentity(size_t index) {
    int subentities_count = GetSubEntitiesCount();

    if (index < subentities_count)
        return &(subentities_[index]);
    else
        return nullptr;
}

Coordinates Entity::GetCoordinates() {
    return coordinates_;
}

void Entity::SetCoordinates(const Coordinates& new_pos) {
    coordinates_ = new_pos;
}

std::ostream& operator<<(std::ostream& stream, Entity& entity) {
    for (const auto& ability : entity.abilities_)
        stream << "AbilityKind - " << ability.first << ", Ability:" << ability.second << std::endl;

    return stream;
}

bool operator==(Entity& entity1, Entity& entity2) {
    return entity1.id_ == entity2.id_;
}

bool Entity::CheckIfInRange(const Entity& target) const {
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

//====================
// entity controller
