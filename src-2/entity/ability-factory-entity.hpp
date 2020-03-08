#pragma once

#include "abilities-entity.hpp"
#include "../ability/ability.hpp"

class AbilityFactoryEntity {
public:
  static Ability<AbilityKindEntity, AbilityStateEntity> CreateAbilityMortal(const int hp_max,
                                                                            const int hp_cur);
  static Ability<AbilityKindEntity, AbilityStateEntity> CreateAbilityContainer(const int capacity);
  static Ability<AbilityKindEntity, AbilityStateEntity> CreateAbilityLockable(const int lock_level);
  static Ability<AbilityKindEntity, AbilityStateEntity> CreateAbilityConsumable();

private:
protected:
};

class AbilityFactoryEntityActive {
public:
  static AbilityActive<AbilityKindEntityActive, AbilityStateEntityActive>
  CreateAbilityMove(const int movability);
  static AbilityActive<AbilityKindEntityActive, AbilityStateEntityActive>
  CreateAbilityKick(const int damage_base);
  static AbilityActive<AbilityKindEntityActive, AbilityStateEntityActive>
      CreateAbilityPick(/* FIXME */);
  static AbilityActive<AbilityKindEntityActive, AbilityStateEntityActive>
  CreateAbilityLoot(const int spot_to_loot);
  static AbilityActive<AbilityKindEntityActive, AbilityStateEntityActive>
  CreateAbilityHack(const int hack_level_base);
  static AbilityActive<AbilityKindEntityActive, AbilityStateEntityActive>
      CreateAbilityConsume(/* FIXME */);

private:
protected:
};