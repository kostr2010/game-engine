#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "factories/entity-factory.hpp"

// finished stuff
// [+] Coord -> ability "IsPositioned", only for tiles
// [+] bool AbleToReach(source, origin, range)
// [+] enum AbiltyResult as the dispatcher's & Apply's return value
// [+] revise structure
// [+] enum -> class enum

// tests:
// [-] test for each ability
// [-] coverage setup

// prepod's doyeba:
// [-] CanDie -> IsMortal
// [-] split abilities into 2 groups: Can*, Is* where Can* has dispatcher but Is* - not (Can* -
// AbilityAction, Is* - AbilityMarker)
// [-] vector<Tile>& GetVisibleTilesInRange(Entity& origin, int range)
// [-] abilities -> abilitiesEntity + abilitiesTile + abilitiesMap(?) (???dispatchers???)
// [-] think'bout separatin' those damn entiddies in several classes (entity -> active, passive)
// [!] EntityActive can only be a child of Tile; EntityPassive is a child of any Entity or (Tile ==
// Entity)
// [-] new move as dispatcher (Entity&, Tile&)
// [!] moving is function of Map which is Map.Move(Entity* entity, Tile* targetTile). it moves
// entity from entity->parentTile to targetTile
// [!] Map is Entity2Entity interaction middleware - limits and controls interaction between
// entities (conditions)
// [-] sometimes Tile is Entity but sometimes Tile is Tile :thinking: (!!!Tile is tILE!!!)
// [-] move dispatchers to Entity class virtual method
// [-] parent Entity* -> parentTile Tile*, parentEntity Entity*

// max program:
// [-] MAX: add equip (subentities -> map<int, Entity>) (new id === last id + 1)
// [-] MAX: construct a battlefield^c simulation

// OMEGA STAGE in progress

using namespace std;

class Map {
public:
  vector<Tile> tiles;
  int          width, height;

private:
protected:
};

class Tile {
public:
  vector<Entity> subentities;
  int            x, y;

private:
protected:
};

void PrintRes(const string& ability, AbilityResult res) {
  switch (res) {
  case AbilityResult::Success:
    cout << ability << " successfully applied" << endl;
    break;
  case AbilityResult::Undefined:
    cout << ability << "'s result is undefined" << endl;
    break;
  case AbilityResult::NoDispatcher:
    cout << ability << " has no dispatcher, not applied" << endl;
    break;
  case AbilityResult::ConditionsNotMet:
    cout << ability << " wasn't applied. conditions weren't met" << endl;
    break;
  case AbilityResult::OriginDoesntHaveAbility:
    cout << ability << " isn't avaliable for this entity" << endl;
    break;
  }

  return;
}

int main() {
  /*
  Entity world_map = EntityFactory::CreateMapShell();
  EntityFactory::InitMap(&world_map, 10, 10);
  */
  /*
   Entity world_map = EntityFactory::CreateMap(10, 10);

   AbilityResult res = AbilityResult::Success;

   Entity ch1   = EntityFactory::CreateWarrior(world_map.GetSubentity(1));
   Entity ch2   = EntityFactory::CreateWarrior(world_map.GetSubentity(2));
   Entity chest = EntityFactory::CreateChest(world_map.GetSubentity(3), 1);
   Entity food  = EntityFactory::CreateFood(world_map.GetSubentity(4));

   chest.AddSubentity({food, food});

   res = ch1.Apply(AbilityKind::CanPick, food);

   PrintRes("CanPick", res);

   ch1.abilities_[AbilityKind::CanLoot].SetStateValue(AbilityState::SpotToLoot, 0);
   res = ch1.Apply(AbilityKind::CanLoot, chest);

   PrintRes("CanLoot", res);

   res = ch1.Apply(AbilityKind::CanKick, ch2);

   PrintRes("CanKick", res);

   cout << ch1 << endl;
   cout << ch2 << endl;
   cout << chest << endl;
   cout << food << endl;

  */

  return 0;
}