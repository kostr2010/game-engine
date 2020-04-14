// utils
#include "./monitor/monitor.hpp"
#include "./utils/log.hpp"

// systems
#include "./system/systems/systemContainer.hpp"
#include "./system/systems/systemHealth.hpp"
#include "./system/systems/systemKick.hpp"

// components
#include "./component/components/health.hpp"
#include "./component/components/movement.hpp"

// TO GOOGLE
// [-] кд дерево
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
// deactivate instead of delete

int main() {
  Monitor monitor{};

  Component comp_health_id  = monitor.RegisterComponent<ComponentHealth>();
  Component comp_kick_id    = monitor.RegisterComponent<ComponentKick>();
  Component comp_contain_id = monitor.RegisterComponent<ComponentContainer>();

  monitor.RegisterSystem<SystemHealth>({comp_health_id});
  SystemKick*      sys_kick = monitor.RegisterSystem<SystemKick>({comp_kick_id});
  SystemContainer* sys_cont = monitor.RegisterSystem<SystemContainer>({comp_contain_id});

  // TODO: wrap into factories
  Entity ch1   = monitor.AddEntity();
  Entity ch2   = monitor.AddEntity();
  Entity chest = monitor.AddEntity();
  Entity item  = monitor.AddEntity();

  ComponentHealth ch1_health = {.hp_max = 10, .hp_cur = 10};
  ComponentHealth ch2_health = {.hp_max = 25, .hp_cur = 25};

  ComponentContainer ch1_inventory   = {};
  ComponentContainer chest_inventory = {{item}};

  ComponentKick ch1_kick = {.damage_amount = 3};

  monitor.AttachProperty(item, Pickable);

  monitor.AttachComponent(ch2, ch2_health);
  monitor.AttachComponent(chest, chest_inventory);
  monitor.AttachComponent(ch1, ch1_inventory);

  std::cout << "chest: " << *monitor.GetComponent<ComponentContainer>(chest)
            << "| ch1: " << *monitor.GetComponent<ComponentContainer>(ch1) << std::endl;

  sys_kick->Kick(ch1, ch2);

  sys_cont->Transfer(chest, item, ch1);

  std::cout << "chest: " << *monitor.GetComponent<ComponentContainer>(chest)
            << "| ch1: " << *monitor.GetComponent<ComponentContainer>(ch1) << std::endl;

  return 0;
}
