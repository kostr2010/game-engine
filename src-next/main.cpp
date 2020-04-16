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
// [?] stackoverflow.com/questions/400257/how-can-i-pass-a-class-member-function-as-a-callback

// FOR NEXT TIME
// [-] UI thread to read console commands
// [-] (type2*)(type1*) -> static / dynamic cast
// [-] read / write from / to disc (serialization)
// [-] make spawner - smth that calls factory and checks needed conditions & requirements

// TO TRY
// [-] systems as static class (it only contains functions anyways)

// DONE
// [+] virtual destructor, where and why -> effective c++ #1
// [+] how shared_ptr works
// [+] make_shared, shared_ptr
// [+] static vs dynamic type, cast
// [+] !!! unique_ptr
// [+] add response codes
// [+] get rid of booleans in components (! new bitmap and manager)
// [+] deactivate instead of delete

int main() {
  Monitor monitor{};

  Component comp_contain_id = monitor.RegisterComponent<ComponentContainer>();

  SystemContainer* sys_cont = monitor.RegisterSystem<SystemContainer>({comp_contain_id});

  Entity ch1   = monitor.AddEntity();
  Entity chest = monitor.AddEntity();
  Entity item  = monitor.AddEntity();

  ComponentContainer ch1_inventory   = {};
  ComponentContainer chest_inventory = {{item}};

  monitor.AttachProperty(item, Pickable);

  monitor.AttachComponent(chest_inventory, chest);
  monitor.AttachComponent(ch1_inventory, ch1);

  sys_cont->Transfer(chest, item, ch1);

  ComponentContainer* ch1_inventory_after   = monitor.GetComponent<ComponentContainer>(ch1);
  ComponentContainer* chest_inventory_after = monitor.GetComponent<ComponentContainer>(chest);

  return 0;
}
