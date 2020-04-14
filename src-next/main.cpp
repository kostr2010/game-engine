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
// [-] (type2*)(type1*) -> static / dynamic cast
// [-] UI thread to read console commands
// [-] read / write to disc

// TO TRY
// [-] systems as static class (it only contains functions anyways)
// [-] get rid of booleans in components (! new bitmap and manager)
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

  monitor.AttachComponent(chest, chest_inventory);
  monitor.AttachComponent(ch1, ch1_inventory);

  sys_cont->Transfer(chest, item, ch1);

  ComponentContainer* ch1_inventory_after   = monitor.GetComponent<ComponentContainer>(ch1);
  ComponentContainer* chest_inventory_after = monitor.GetComponent<ComponentContainer>(chest);

  return 0;
}
