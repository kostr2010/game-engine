#include <algorithm>
#include <cmath>
#include <limits>
#include <tuple>
#include <vector>

#include "entity/entity.hpp"
#include "monitor/monitor.hpp"
#include "system/system.hpp"
#include "utils/vec2.hpp"

#define log(text) std::cout << text << std::endl

struct SCPComponentPosition {
  int x, y;
};

struct SCPComponentEuclid {
  int damage;
};

struct SCPComponentHealth {
  int hp;
};

struct SCPComponentMovement {
  int speed;
};

// sometimes we need to define empty structure to identify a class of entities
struct SCPComponentHuman {};

std::ostream& operator<<(std::ostream& os, SCPComponentPosition& comp) {
  return os << "x: " << comp.x << ", y: " << comp.y;
}

std::ostream& operator<<(std::ostream& os, SCPComponentEuclid& comp) {
  return os << "damage: " << comp.damage;
}

std::ostream& operator<<(std::ostream& os, SCPComponentHealth& comp) {
  return os << "hp " << comp.hp;
}

std::ostream& operator<<(std::ostream& os, SCPComponentMovement& comp) {
  return os << "speed " << comp.speed;
}

std::ostream& operator<<(std::ostream& os, SCPComponentHuman& comp) {
  return os << "is human";
}

class Factory {
public:
  static EntityId SpawnSCP173(Monitor* monitor, int x, int y) {
    EntityId scp = monitor->AddEntity();

    SCPComponentPosition position = {.x = x, .y = y};
    SCPComponentEuclid   euclid   = {.damage = 10};
    SCPComponentMovement movement = {.speed = 5};
    SCPComponentHealth   health   = {.hp = 10};

    monitor->AttachComponent(position, scp);
    monitor->AttachComponent(euclid, scp);
    monitor->AttachComponent(movement, scp);
    monitor->AttachComponent(health, scp);

    LOG_LVL_MONITOR_ROUTINE("scp173 spawned as " << scp << " at {" << x << ", " << y << "}");

    return scp;
  }

  static EntityId SpawnHuman(Monitor* monitor, int x, int y) {
    EntityId human = monitor->AddEntity();

    SCPComponentPosition position   = {.x = x, .y = y};
    SCPComponentHealth   health     = {.hp = 5};
    SCPComponentMovement movement   = {.speed = 1};
    SCPComponentHuman    human_comp = {};

    monitor->AttachComponent(position, human);
    monitor->AttachComponent(health, human);
    monitor->AttachComponent(movement, human);
    monitor->AttachComponent(human_comp, human);

    LOG_LVL_MONITOR_ROUTINE("human spawned as " << human << " at {" << x << ", " << y << "}");

    return human;
  }
};

std::tuple<int, int> GetOffset(SCPComponentPosition* comp_pos_origin,
                               SCPComponentPosition* comp_pos_target) {
  int dx = comp_pos_target->x - comp_pos_origin->x;
  int dy = comp_pos_target->y - comp_pos_origin->y;

  return {dx, dy};
}

int GetDistance(SCPComponentPosition* comp_pos_origin, SCPComponentPosition* comp_pos_target) {
  auto [dx, dy] = GetOffset(comp_pos_origin, comp_pos_target);
  return (int)std::sqrt(dx * dx + dy * dy);
}

class SCPSystemHuman : public System {
public:
  SCPSystemHuman(Monitor* monitor) : System(monitor) {
  }

  std::vector<ComponentType> GetRequiredComponentTypes() override {
    return {monitor_->RegisterComponent<SCPComponentPosition>(),
            monitor_->RegisterComponent<SCPComponentMovement>(),
            monitor_->RegisterComponent<SCPComponentHuman>()};
  }
};

class SCPSystemMovement : public System {
public:
  SCPSystemMovement(Monitor* monitor) : System(monitor) {
  }

  ResponseCode MoveBy(EntityId entity, int dx, int dy) {
    if (dx != 0 && dy != 0)
      return ResponseCode::Failure;

    SCPComponentMovement* comp_mov = monitor_->GetComponent<SCPComponentMovement>(entity);

    int dist = std::max(dx, dy);
    if (dist > comp_mov->speed)
      return ResponseCode::Failure;

    SCPComponentPosition* comp_pos = monitor_->GetComponent<SCPComponentPosition>(entity);
    comp_pos->x += dx;
    comp_pos->y += dy;
  }

  ResponseCode MoveTo(EntityId entity_origin, EntityId entity_target) {
    SCPComponentPosition* comp_pos_origin =
        monitor_->GetComponent<SCPComponentPosition>(entity_origin);
    SCPComponentPosition* comp_pos_target =
        monitor_->GetComponent<SCPComponentPosition>(entity_target);

    SCPComponentMovement* comp_mov_origin =
        monitor_->GetComponent<SCPComponentMovement>(entity_origin);

    auto [dx_raw, dy_raw] = GetOffset(comp_pos_origin, comp_pos_target);

    int dx = std::min(dx_raw, comp_mov_origin->speed);
    int dy = std::min(dy_raw, comp_mov_origin->speed);

    log("dx = " << dx << ", dy = " << dy);
    // choose the closest
    if (std::abs(dx) > std::abs(dy))
      comp_pos_origin->x += dx;
    else
      comp_pos_origin->y += dy;

    return ResponseCode::Success;
  }

  std::vector<ComponentType> GetRequiredComponentTypes() override {
    return {monitor_->RegisterComponent<SCPComponentPosition>(),
            monitor_->RegisterComponent<SCPComponentMovement>()};
  }
};

class SCPSystemHealth : public System {
public:
  SCPSystemHealth(Monitor* monitor) : System(monitor) {
  }

  ResponseCode ChangeHp(EntityId entity_target, int delta) {
    SCPComponentHealth* comp_health = monitor_->GetComponent<SCPComponentHealth>(entity_target);

    std::cout << "entity " << entity_target << " health changed by " << delta << " to "
              << comp_health->hp + delta << std::endl;
    comp_health->hp += delta;

    return ResponseCode::Success;
  }

  ResponseCode RemoveDeadEntities() {
    auto entity = entities_.begin();

    while (entity != entities_.end()) {
      SCPComponentHealth* comp_health = monitor_->GetComponent<SCPComponentHealth>(*entity);
      bool                alive       = comp_health->hp > 0;

      if (!alive)
        monitor_->RemoveEntity(*(entity++));
      else
        ++entity;
    }

    return ResponseCode::Success;
  }

  std::vector<ComponentType> GetRequiredComponentTypes() override {
    return {monitor_->RegisterComponent<SCPComponentHealth>()};
  }
};

class SCPSystemEuclid : public System {
public:
  SCPSystemEuclid(Monitor* monitor) : System(monitor) {
  }

  ResponseCode TeleportToClosest(EntityId entity) {
    EntityId entity_closest;
    int      dist_closest = std::numeric_limits<int>::max();

    SCPSystemHuman*       sys_human       = monitor_->GetSystem<SCPSystemHuman>();
    SCPComponentPosition* comp_pos_origin = monitor_->GetComponent<SCPComponentPosition>(entity);

    // getting the closest human-entity
    for (auto& entity_target : sys_human->entities_) {
      SCPComponentPosition* comp_pos_target =
          monitor_->GetComponent<SCPComponentPosition>(entity_target);
      int dist = GetDistance(comp_pos_origin, comp_pos_target);

      if (dist < dist_closest) {
        dist_closest   = dist;
        entity_closest = entity_target;
      }
    }

    SCPSystemMovement* sys_mov = monitor_->GetSystem<SCPSystemMovement>();

    log("entity " << entity << " is moving to " << entity_closest);

    sys_mov->MoveTo(entity, entity_closest);

    return ResponseCode::Success;
  }

  std::vector<ComponentType> GetRequiredComponentTypes() override {
    return {monitor_->RegisterComponent<SCPComponentPosition>(),
            monitor_->RegisterComponent<SCPComponentEuclid>()};
  }

  ResponseCode DealDamage(EntityId entity_origin, EntityId entity_target) {

    SCPComponentPosition* comp_pos_origin =
        monitor_->GetComponent<SCPComponentPosition>(entity_origin);
    SCPComponentPosition* comp_pos_target =
        monitor_->GetComponent<SCPComponentPosition>(entity_target);

    std::cout << "entity " << entity_origin << "(" << comp_pos_origin->x << ", "
              << comp_pos_origin->y << ")"
              << " attempts to DealDamage to " << entity_target << "(" << comp_pos_target->x << ", "
              << comp_pos_target->y << ")" << std::endl;

    int dist = GetDistance(comp_pos_origin, comp_pos_target);

    if (dist != 0)
      return ResponseCode::Failure;

    SCPComponentEuclid* comp_eu = monitor_->GetComponent<SCPComponentEuclid>(entity_origin);

    SCPSystemHealth* sys_health = monitor_->GetSystem<SCPSystemHealth>();

    sys_health->ChangeHp(entity_target, -1 * comp_eu->damage);

    log("dealt damage successfully");
    return ResponseCode::Success;
  }

private:
  void RegisterDependentSystems() override {
    monitor_->RegisterSystem<SCPSystemHuman>();
    monitor_->RegisterSystem<SCPSystemMovement>();
  }
};

int main() {
  log("start");

  Monitor monitor{};

  SCPSystemHealth*   sys_hp  = monitor.RegisterSystem<SCPSystemHealth>();
  SCPSystemMovement* sys_mov = monitor.RegisterSystem<SCPSystemMovement>();
  SCPSystemEuclid*   sys_eu  = monitor.RegisterSystem<SCPSystemEuclid>();
  SCPSystemHuman*    sys_hum = monitor.RegisterSystem<SCPSystemHuman>();

  // // S.........
  // // .......2..
  // // ..........
  // // ..........
  // // ..........
  // // .....1....
  // // ..........
  // // ..........
  // // ..........
  // // ..........
  // // .........3

  EntityId scp173 = Factory::SpawnSCP173(&monitor, 0, 0);
  log("scp173 id " << scp173);
  EntityId subj1 = Factory::SpawnHuman(&monitor, 5, 5);
  EntityId subj2 = Factory::SpawnHuman(&monitor, 7, 1);
  EntityId subj3 = Factory::SpawnHuman(&monitor, 9, 9);

  int tick = 0;
  while (!sys_hum->entities_.empty() && tick < 10) {
    log("\n// ====================\n"
        << "// TICK: " << tick++ << "\n");

    for (auto entity_euclid : sys_eu->entities_) {
      sys_eu->TeleportToClosest(entity_euclid);

      for (auto entity_human : sys_hum->entities_) {
        sys_eu->DealDamage(entity_euclid, entity_human);
      }
    }

    log("removing dead entities");
    sys_hp->RemoveDeadEntities();
    log("removed dead entities");

    for (const auto entity : sys_hum->entities_) {
      log(entity << " is alive");
    }
  }

  log("finished");

  return 0;
}