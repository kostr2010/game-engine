#include "./model.hpp"
#include <vector>

int main() {
  EntityActive character1 = EntityFactoryActive::CreateWarrior();
  EntityActive character2 = EntityFactoryActive::CreateWarrior();
  EntityActive character3 = EntityFactoryActive::CreateWarrior();

  Entity obj1 = EntityFactory::CreateThing();
  Entity obj2 = EntityFactory::CreateThing();
  Entity obj3 = EntityFactory::CreateThing();
  Entity obj4 = EntityFactory::CreateThing();

  std::vector<Tile> tiles = {
      Tile(nullptr, {obj1}, {character1}), // 0:0
      Tile(nullptr, {}, {character2}),     // 0:1
      Tile(nullptr, {}, {}),               // 0:2
      Tile(nullptr, {}, {}),               // 1:0
      Tile(nullptr,
           {
               obj2,
               obj3,
           },
           {}),                            // 1:1
      Tile(nullptr, {}, {}),               // 1:2
      Tile(nullptr, {}, {}),               // 2:0
      Tile(nullptr, {}, {}),               // 2:1
      Tile(nullptr, {}, {}),               // 2:2
      Tile(nullptr, {}, {}),               // 3:0
      Tile(nullptr, {obj4}, {character3}), // 3:1
      Tile(nullptr, {}, {}),               // 3:2
      Tile(nullptr, {}, {}),               // 4:0
      Tile(nullptr, {}, {}),               // 4:1
      Tile(nullptr, {}, {}),               // 4:2
  };

  Map world_map(tiles, 5, 3);

  world_map.ApplyAbility();
}