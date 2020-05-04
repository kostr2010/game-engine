// utils
#include "./monitor/monitor.hpp"
#include "./utils/log.hpp"

// systems
#include "./system/systems/systemConsole.hpp"
#include "./system/systems/systemContainer.hpp"
#include "./system/systems/systemHealth.hpp"
#include "./system/systems/systemKick.hpp"
#include "./system/systems/systemMovement.hpp"
#include "./system/systems/systemTerrain.hpp"

// components
#include "./component/components/health.hpp"
#include "./component/components/movement.hpp"

#include <iostream>
#include <mutex>
#include <string>
#include <thread>

// TO GOOGLE
// [-] кд дерево
// [?] stackoverflow.com/questions/400257/how-can-i-pass-a-class-member-function-as-a-callback

// FOR NEXT TIME
// [-] UI thread to read console commands
// [-] (type2*)(type1*) -> static / dynamic cast
// [-] read / write from / to disc (serialization)
// [-] make spawner - smth that calls factory and checks needed conditions & requirements

// DONE
// [+] padding
// [+] movement
// [+] virtual destructor, where and why -> effective c++ #1
// [+] how shared_ptr works
// [+] make_shared, shared_ptr
// [+] static vs dynamic type, cast
// [+] !!! unique_ptr
// [+] add response codes
// [+] get rid of booleans in components (! new bitmap and manager)
// [+] deactivate instead of delete

std::vector<std::string> messages;
std::mutex               messages_mutex;

void userInput() {
  while (true) {
    std::string input;
    std::getline(std::cin, input);

    std::lock_guard<std::mutex> guard(messages_mutex);

    messages.push_back(input);
  }
}

void printer() {
  while (true) {
    std::lock_guard<std::mutex> guard(messages_mutex);
    // std::string message_last = messages.back();
    if (messages.empty())
      continue;

    std::cout << messages.back() << std::endl;

    messages.pop_back();
  }
}

int main() {
  std::cout << "start" << std::endl;
  // std::thread t1(userInput);
  // std::thread t2(printer);

  // t1.join();
  // t2.join();

  // Monitor monitor{};

  // ComponentType comp_contain_id = monitor.RegisterComponent<ComponentContainer>();

  // SystemContainer* sys_cont = monitor.RegisterSystem<SystemContainer>();

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

  Monitor  monitor{};
  Monitor* monitor_ptr = &monitor;

  // ComponentType comp_id_pos      = monitor.RegisterComponent<ComponentPosition>();
  // ComponentType comp_id_movement = monitor.RegisterComponent<ComponentMovement>();
  // ComponentType comp_id_terrain  = monitor.RegisterComponent<ComponentTerrain>();

  SystemMovement* sys_movement = monitor.RegisterSystem<SystemMovement>();
  monitor.RegisterSystem<SystemTerrain>();
  SystemConsole* sys_console = monitor.RegisterSystem<SystemConsole>();

  monitor.StartLoop();

  return 0;
}
