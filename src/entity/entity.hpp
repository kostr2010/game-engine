#pragma once

#include <map>
#include <vector>

#include "../ability/ability.hpp"

enum class EntityPassiveKind {
    blank,
    chest,
    door,
    pistol,
    pistol_ammo,
};

enum class EntityActiveKind {
    engineer,
    sniper,

    turret,
};

class EntityPassive {
  public:
    EntityPassive()  = default;
    ~EntityPassive() = default;

    EntityPassive(int id, EntityPassiveKind kind, std::vector<EntityPassive> subentities,
                  std::map<AbilityKindPassive, AbilityPassive> abilities_passive);

  private:
    EntityPassiveKind kind_;

  protected:
    int id_;

    std::vector<EntityPassive> subentities_;

    std::map<AbilityKindPassive, AbilityPassive> abilities_passive_;
};

class EntityActive : public EntityPassive {
  public:
    EntityActive()  = default;
    ~EntityActive() = default;

    EntityActive(int id, EntityActiveKind kind, std::vector<EntityPassive> subentities,
                 std::map<AbilityKindPassive, AbilityPassive> abilities_passive,
                 std::map<AbilityKindActive, AbilityActive>   abilities_active);

  private:
    EntityActiveKind kind_;

    std::map<AbilityKindActive, AbilityActive> abilities_active_;
};
