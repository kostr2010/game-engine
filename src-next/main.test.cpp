#define CATCH_CONFIG_MAIN
#include "../libs/catch2/catch2.hpp"

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

TEST_CASE("Kick") {
  Monitor monitor{};

  Component comp_health_id  = monitor.RegisterComponent<ComponentHealth>();
  Component comp_kick_id    = monitor.RegisterComponent<ComponentKick>();
  Component comp_contain_id = monitor.RegisterComponent<ComponentContainer>();

  monitor.RegisterSystem<SystemHealth>({comp_health_id});
  SystemKick*      sys_kick = monitor.RegisterSystem<SystemKick>({comp_kick_id});
  SystemContainer* sys_cont = monitor.RegisterSystem<SystemContainer>({comp_contain_id});

  Entity ch1 = monitor.AddEntity();
  Entity ch2 = monitor.AddEntity();

  ComponentHealth ch1_health = {.hp_max = 10, .hp_cur = 10};
  ComponentHealth ch2_health = {.hp_max = 25, .hp_cur = 25};

  ComponentContainer chest_inventory = {};

  ComponentKick ch1_kick = {.damage_amount = 3};

  monitor.AttachComponent(ch1, ch1_health);
  monitor.AttachComponent(ch2, ch2_health);

  monitor.AttachComponent(ch1, ch1_kick);

  sys_kick->Kick(ch1, ch2);

  ComponentHealth* ch1_health_after = monitor.GetComponent<ComponentHealth>(ch1);
  ComponentHealth* ch2_health_after = monitor.GetComponent<ComponentHealth>(ch2);

  REQUIRE(ch1_health_after->hp_cur == 10);
  REQUIRE(ch2_health_after->hp_cur == 22);
}

TEST_CASE("Transfer") {
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

  // check if chest has no item
  REQUIRE(std::find(chest_inventory_after->subentities_.begin(),
                    chest_inventory_after->subentities_.end(),
                    item) == chest_inventory_after->subentities_.end());

  // check if ch1 has item
  REQUIRE(std::find(ch1_inventory_after->subentities_.begin(),
                    ch1_inventory_after->subentities_.end(),
                    item) != ch1_inventory_after->subentities_.end());
}