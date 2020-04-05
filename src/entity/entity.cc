#include "./entity.hpp"

EntityPassive::EntityPassive(int id, EntityPassiveKind kind, std::vector<EntityPassive> subentities,
                             std::map<AbilityKindPassive, AbilityPassive> abilities_passive) {
    id_                = id;
    kind_              = kind;
    subentities_       = subentities;
    abilities_passive_ = abilities_passive;
}

EntityActive::EntityActive(int id, EntityActiveKind kind, std::vector<EntityPassive> subentities,
                           std::map<AbilityKindPassive, AbilityPassive> abilities_passive,
                           std::map<AbilityKindActive, AbilityActive>   abilities_active) {
    id_                = id;
    kind_              = kind;
    subentities_       = subentities;
    abilities_passive_ = abilities_passive;
    abilities_active_  = abilities_active;
}