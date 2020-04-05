#include <list>
#include <map>
#include <string>
#include <vector>

#include "./component/component.hpp"
#include "./effect/effect.hpp"
#include "./entity/entity.hpp"
#include "./system/system.hpp"

// ABILITY IS POD (PLAIN OLD DATAAAAAAAAAAAAAAAAAAAAAAA)

const Entity MAX_ENTITIES   = 100;
const int    MAX_COMPONENTS = 100;

/*

struct Material {
  int mass, width, height, length;
};

struct Mortal {
  int hp_max, hp_cur;
};

struct Intelligent {
  AI ai;
};

...

int main() {
  Monitor monitor{};

  monitor.Initialize();

  monitor.component_manager.RegisterComponent<Mortal>();
  monitor.component_manager.RegisterComponent<Material>();
  monitor.component_manager.RegisterComponent<Intelligent>();

  monitor.system_manager.RegisterSystem<HealthSystem>();


}

*/