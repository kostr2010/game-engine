#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <vector>

#include "../constants/dict-ability-dispatcher.hpp"
#include "main-classes.hpp"

//====================
// METHODS IMPLEMENTATION

//====================
// ability

Ability::Ability() {
    return;
}

Ability::Ability(const AbilityKind& kind, const std::map<AbilityState, int>& init_state) {
    state_ = init_state;
    kind_  = kind;
}

int Ability::GetStateValue(const AbilityState& state_name) { // operator[]  conflicts with const because returns lvalue? aka type&
    return state_[state_name];
}

void Ability::SetStateValue(const AbilityState& state_name, const int new_value) {
    state_[state_name] = new_value;
}

bool operator==(const Ability& left, const Ability& right) {
    return left.state_ == right.state_;
}

std::ostream& operator<<(std::ostream& stream, const Ability& ability) {
    // stream << ability.kind_ << ": ";

    for (const auto& s : ability.state_)
        stream << s.second << " ";

    return stream;
}

//====================
// entity

Entity::Entity(const EntityKind& kind, Entity* parent, const std::vector<Ability>& abilities /*= {}*/,
               const std::vector<Entity>& subentities /*= {}*/) {
    subentities_ = subentities;
    parent_      = parent;
    kind_        = kind;

    id_ = sole::uuid1(); // unique id for the entity

    if (parent != nullptr)
        parent->subentities_.push_back(*this); // check if works

    for (const auto& ability : abilities)
        abilities_[ability.kind_] = ability;
}

AbilityResult Entity::Apply(const AbilityKind& kind, Entity& target) {
    if (abilities_.count(kind) != 0)
        return dict_ability_dispatcher[kind](*this, target);
    else
        return AbilityResult::OriginDoesntHaveAbility;
}

Entity* Entity::GetParentTile() const {
    if (parent_ == nullptr)
        throw std::string("no appropriate parent");

    if (parent_->kind_ == EntityKind::Tile)
        return parent_;
    else
        return parent_->GetParentTile();
}

int Entity::GetSubEntitiesCount() const {
    return subentities_.size();
}

void Entity::AddSubentity(const std::vector<Entity>& items) {
    if (abilities_.count(AbilityKind::CanContain) == 0)
        return;

    for (const Entity& item : items) {
        bool can_fit       = subentities_.size() < abilities_[AbilityKind::CanContain].GetStateValue(AbilityState::ContainCapacity);
        bool can_be_picked = item.abilities_.count(AbilityKind::CanBePicked) != 0;

        if (can_fit && can_be_picked)
            subentities_.push_back(item);
        else if (!can_fit)
            break;
    }

    return;
}

void Entity::RemoveSubentity(size_t index) {
    if (abilities_.count(AbilityKind::CanContain) == 0)
        return;

    if (index < subentities_.size())
        subentities_.erase(subentities_.begin() + index);

    return;
}

Entity* Entity::GetSubentity(size_t index) {
    int subentities_count = GetSubEntitiesCount();

    if (index < subentities_count)
        return &(subentities_[index]); // & - non-const operator? when ttrying to add "const" to
    else
        return nullptr;
}

bool Entity::CheckIfInRange(const Entity& target, AbilityKind ability) const {
    Entity* parent_tile = this->GetParentTile();

    int map_size_x = parent_tile->parent_->abilities_[AbilityKind::IsMap].GetStateValue(AbilityState::MapWidth);
    int map_size_y = parent_tile->parent_->abilities_[AbilityKind::IsMap].GetStateValue(AbilityState::MapHeight);
    int pos_x      = parent_tile->abilities_[AbilityKind::IsPositioned].GetStateValue(AbilityState::PositionX);
    int pos_y      = parent_tile->abilities_[AbilityKind::IsPositioned].GetStateValue(AbilityState::PositionY);

    // index of (x, y) = y * size_x + x
}

std::ostream& operator<<(std::ostream& stream, const Entity& entity) {
    for (const auto& ability : entity.abilities_)
        stream << "AbilityKind - " /*<< ability.first*/ << ", Ability:" << ability.second << std::endl;

    return stream;
}

bool operator==(const Entity& entity1, const Entity& entity2) {
    return entity1.id_ == entity2.id_;
}
