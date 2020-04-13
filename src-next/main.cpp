// utils
#include "./monitor/monitor.hpp"
#include "./utils/log.hpp"

// systems
#include "./system/systems/systemHealth.hpp"
#include "./system/systems/systemKick.hpp"

// components
#include "./component/components/health.hpp"
#include "./component/components/movement.hpp"

// TO GOOGLE
// [-] how shared_ptr works
// [-] make_shared, shared_ptr
// [-] static vs dynamic type, cast
// [-] !!! unique_ptr
// [-] stackoverflow.com/questions/400257/how-can-i-pass-a-class-member-function-as-a-callback
// [-] virtual destructor, where and why -> effective c++ #1

// FOR NEXT TIME
// [-] add response codes
// (type2*)(type1*) -> static / dynamic cast

// TO TRY
// [-] systems as static class (it only contains functions anyways)
// [-] get rid of booleans in components (! new bitmap and manager)

int main() {
  LOG_LVL_SYSTEM_CLEAR();

  Monitor monitor{};

  Component comp_health_id = monitor.RegisterComponent<ComponentHealth>();
  Component comp_kick_id   = monitor.RegisterComponent<ComponentKick>();

  monitor.RegisterSystem<SystemHealth>({comp_health_id});
  SystemKick* sys_kick = (SystemKick*)monitor.RegisterSystem<SystemKick>({comp_kick_id});

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
