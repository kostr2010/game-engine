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

#include "./factories/factories.hpp"

#include "./utils/response.hpp"

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

  monitor.AttachComponent(ch1_health, ch1);
  monitor.AttachComponent(ch2_health, ch2);

  monitor.AttachComponent(ch1_kick, ch1);

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

  monitor.AttachComponent(chest_inventory, chest);
  monitor.AttachComponent(ch1_inventory, ch1);

  sys_cont->Transfer(chest, item, ch1);

  ComponentContainer* ch1_inventory_after   = monitor.GetComponent<ComponentContainer>(ch1);
  ComponentContainer* chest_inventory_after = monitor.GetComponent<ComponentContainer>(chest);

  // check if chest has no item
  REQUIRE(std::find(chest_inventory_after->subentities.begin(),
                    chest_inventory_after->subentities.end(),
                    item) == chest_inventory_after->subentities.end());

  // check if ch1 has item
  REQUIRE(std::find(ch1_inventory_after->subentities.begin(),
                    ch1_inventory_after->subentities.end(),
                    item) != ch1_inventory_after->subentities.end());
}

TEST_CASE("Move") {
  Monitor monitor{};

  Component comp_id_pos      = monitor.RegisterComponent<ComponentPosition>();
  Component comp_id_movement = monitor.RegisterComponent<ComponentMovement>();

  SystemMovement* sys_movement = monitor.RegisterSystem<SystemMovement>({comp_id_movement});

  Entity ch1 = monitor.AddEntity();

  ComponentPosition ch1_pos = {.pos = Vec2{0, 0}};
  ComponentMovement ch1_mov = {.steps_max = 3, .steps_cur = 3};

  monitor.AttachComponent(ch1_pos, ch1);
  monitor.AttachComponent(ch1_mov, ch1);

  sys_movement->Move(ch1, Vec2{1, 0});
  REQUIRE(monitor.GetComponent<ComponentPosition>(ch1)->pos == Vec2{1, 0});

  sys_movement->Move(ch1, Vec2{1, 1});
  REQUIRE(monitor.GetComponent<ComponentPosition>(ch1)->pos == Vec2{2, 1});

  sys_movement->Move(ch1, Vec2{-2, -1});
  REQUIRE(monitor.GetComponent<ComponentPosition>(ch1)->pos == Vec2{0, 0});

  ResponseCode code1 = sys_movement->Move(ch1, Vec2{1, 1});
  REQUIRE(code1 == ResponseCode::Restricted);

  sys_movement->ResetCurrentSteps();
  REQUIRE(monitor.GetComponent<ComponentMovement>(ch1)->steps_cur == 3);

  sys_movement->Move(ch1, Vec2{-1, 0});
  REQUIRE(monitor.GetComponent<ComponentPosition>(ch1)->pos == Vec2{-1, 0});
}