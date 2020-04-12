#pragma once

#include "../monitor/monitor.hpp"
#include "../system/systems/systemHealth.hpp"
#include "../system/systems/systemKick.hpp"
#include "../system/systems/systemMovement.hpp"
#include "../utils/vec2.hpp"

class EntityFactory {
  static void SpawnWarrior(Monitor* monitor, Vec2 position) {
    Entity            entity = monitor->AddEntity();
    ComponentHealth   health = {.hp_max = 10, .hp_cur = 10};
    ComponentMovement move   = {.speed = 1};
    ComponentKick     kick   = {.damage_amount = 3};

    monitor->AttachComponent(entity, health);
    monitor->AttachComponent(entity, move);
    monitor->AttachComponent(entity, kick);
  }

  static void SpawnDummy(Monitor* monitor, Vec2 position) {
    Entity
  }

  static void SpawnChest(Monitor* monitor, Vec2 position) {
  }
};