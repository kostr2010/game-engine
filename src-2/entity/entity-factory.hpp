#pragma once

#include "entity.hpp"

class EntityFactory {
public:
  static Entity CreateChest(int hp, int capacity);
  static Entity CreateThing();

private:
protected:
};

class EntityFactoryActive {
public:
  static EntityActive CreateWarrior();

private:
protected:
};