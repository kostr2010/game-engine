#pragma once

#include <cstdio>

#include "../main-classes/main-classes.hpp"

class Ability;

//====================
// CLASSES DECLARATION

//====================
// ability factory

class AbilityFactory {
public:
  static Ability CreateAbilityDie(const int hp_max, const int hp_current);
  static Ability CreateAbilityContain(const int capacity);
  static Ability CreateAbilityBePicked();
  static Ability CreateAbilityMove(const int movability);
  static Ability CreateAbilityPick();
  static Ability CreateAbilityLoot(/*default value*/);
  static Ability CreateAbilityKick(const int damage);
  static Ability CreateAbilityHack(const int hack_level);
  static Ability CreateAbilityBeLocked(const int lock_level);
  static Ability CreateAbilityIsMap(const int width, const int height);
  static Ability CreateAbilityIsTransparent();
  static Ability CreateAbilityIsWalkable(const int walkability_level);
  static Ability CreateAbilityIsPositioned(const int pos_x, const int pos_y);
  static Ability CreateAbilityCanConsume();
  static Ability CreateAbilityIsConsumable();

private:
protected:
};