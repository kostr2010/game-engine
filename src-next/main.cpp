// systems
#include "./system/systems/systemHealth.hpp"
#include "./system/systems/systemKick.hpp"

// components
#include "./component/components/health.hpp"
#include "./component/components/movement.hpp"

// utiles
#include "./monitor/monitor.hpp"

// how shared_ptr works
// make_shared, shared_ptr
// static vs dynamic type, cast
// !!! unique_ptr

int main() {
  Monitor monitor{};

  Component comp_health_id = monitor.RegisterComponent<ComponentHealth>();
  Component comp_kick_id   = monitor.RegisterComponent<ComponentKick>();

  SystemHealth* sys_health = monitor.RegisterSystem<SystemHealth>({comp_health_id});
  SystemKick*   sys_kick   = monitor.RegisterSystem<SystemKick>({comp_kick_id});

  // TODO: wrap into factories
  Entity ch1 = monitor.AddEntity();
  Entity ch2 = monitor.AddEntity();

  ComponentHealth ch1_health = {.hp_max = 10, .hp_cur = 10};
  ComponentHealth ch2_health = {.hp_max = 25, .hp_cur = 25};

  ComponentKick ch1_kick = {.damage_amount = 3};

  monitor.AttachComponent(ch1, ch1_health);
  monitor.AttachComponent(ch2, ch2_health);

  monitor.AttachComponent(ch1, ch1_kick);

  sys_kick->Kick(ch1, ch2);

  return 0;
}
