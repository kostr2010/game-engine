#include <algorithm>
#include <math.h>
#include <tuple>

#include "entity/entity.hpp"
#include "monitor/monitor.hpp"
#include "system/system.hpp"
#include "utils/vec2.hpp"

struct ComponentPosition {
  int x;
  int y;
};

struct ComponentHealth {
  float head_angle_left;
};

struct ComponentDamage {
  float head_angle_per_turn; // rads/sec
};

struct ComponentEuclid {
  int aggresiveness; // 0 - 10
};

struct ComponentMovement {
  int teleport_distance_per_turn; // meters/sec
};

EntityId SpawnSCP173(Monitor* monitor, int x, int y) {
  EntityId scp = monitor->AddEntity();

  ComponentPosition position = {.x = x, .y = y};
  ComponentDamage   damage   = {.head_angle_per_turn = 25};
  ComponentMovement movement = {.teleport_distance_per_turn = 25};

  monitor->AttachComponent(position, scp);
  monitor->AttachComponent(damage, scp);
  monitor->AttachComponent(movement, scp);

  return scp;
}

EntityId SpawnHuman(Monitor* monitor, int x, int y) {
  EntityId human = monitor->AddEntity();

  ComponentPosition position = {.x = x, .y = y};
  ComponentHealth   health   = {.head_angle_left = 3.14 * 2};

  monitor->AttachComponent(position, human);
  monitor->AttachComponent(health, human);

  return human;
}

class SystemMovement : public System {
  SystemMovement(Monitor* monitor) : System(monitor) {
  }

  ResponseCode MoveToClosest(EntityId entity) {
    EntityId entity_closest;
    int      dist_closest = INFINITY;

    // TODO: complete
  }

  ResponseCode MoveTo(EntityId entity_origin, EntityId entity_target) {
    ComponentPosition* comp_pos_origin = monitor_->GetComponent<ComponentPosition>(entity_origin);
    ComponentPosition* comp_pos_target = monitor_->GetComponent<ComponentPosition>(entity_target);

    ComponentMovement* comp_mov_origin = monitor_->GetComponent<ComponentMovement>(entity_origin);

    auto [dx_raw, dy_raw] = GetDistance(comp_pos_origin, comp_pos_target);

    int dx = std::min(dx_raw, comp_mov_origin->teleport_distance_per_turn);
    int dy = std::min(dy_raw, comp_mov_origin->teleport_distance_per_turn);

    // choose the closest
    if (dx > dy)
      comp_pos_origin->x += dx;
    else
      comp_pos_origin->y += dy;

    return ResponseCode::Success;
  }

private:
  std::tuple<int, int> GetDistance(ComponentPosition* comp_pos_origin,
                                   ComponentPosition* comp_pos_target) {
    int dx = comp_pos_target->x - comp_pos_origin->x;
    int dy = comp_pos_target->y - comp_pos_origin->y;

    return {dx, dy};
  }
};

class SystemHealth : public System {
  SystemHealth(Monitor* monitor) : System(monitor) {
  }

  ResponseCode RotateHead(EntityId entity_target, float angle) {
    std::cout << "entity " << entity_target << " head is tried to rotate by " << angle << " radians"
              << std::endl;

    ComponentDamage* comp_dmg = monitor_->GetComponent<ComponentDamage>(entity_target);

    return ResponseCode::Success;
  }
};

class SystemCombat : public System {
  SystemCombat(Monitor* monitor) : System(monitor) {
  }

  ResponseCode Scrag(EntityId entity_origin, EntityId entity_target) {
    std::cout << "entity " << entity_origin << " attempts to scrag " << entity_target << std::endl;

    ComponentDamage* comp_dmg = monitor_->GetComponent<ComponentDamage>(entity_origin);
    ComponentEuclid* comp_euc = monitor_->GetComponent<ComponentEuclid>(entity_origin);

    SystemHealth* sys_health = monitor_->GetSystem<SystemHealth>();

    sys_health->ChangeCurrentHp(entity_target,
                                -1 * comp_dmg->head_angle_per_turn * comp_euc->aggresiveness);

    return ResponseCode::Success;
  }
};

int main() {
  Monitor monitor{};

  // TODO: complete

  // ComponentType comp_contain_id = monitor.RegisterComponent<ComponentContainer>();

  // SystemContainer* sys_cont = monitor.RegisterSystem<SystemContainer>({comp_contain_id});

  // EntityId ch1   = monitor.AddEntity();
  // EntityId chest = monitor.AddEntity();
  // EntityId item  = monitor.AddEntity();

  // ComponentContainer ch1_inventory   = {};
  // ComponentContainer chest_inventory = {{item}};

  // monitor.AttachProperty(item, Pickable);

  // monitor.AttachComponent(chest_inventory, chest);
  // monitor.AttachComponent(ch1_inventory, ch1);

  // sys_cont->Transfer(chest, item, ch1);

  // ComponentContainer* ch1_inventory_after   = monitor.GetComponent<ComponentContainer>(ch1);
  // ComponentContainer* chest_inventory_after = monitor.GetComponent<ComponentContainer>(chest);

  return 0;
}