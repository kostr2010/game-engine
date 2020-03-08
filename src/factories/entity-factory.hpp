#pragma once
#include <cstdio>

#include "../main-classes/main-classes.hpp"

// class Entity;
// class Coord;

//===================
// CLASSES DECLARATION

//====================
// entity factory

class EntityFactory {
public:
  // heroes
  static Entity CreateWarrior(Entity* parent);

  // enemies
  static Entity CreateMimic(Entity* parent);

  // containers
  static Entity CreateChest(Entity* parent, int lock_lvl,
                            const std::vector<Entity>& subentites = {});

  // items
  static Entity CreateFood(Entity* parent);
  /*
  // misc
  static Entity CreateTile(Entity* parent, int pos_x, int pos_y,
                           int walkability_level); // tile (only tile may be a subentity of a map)
<- how to check? static Entity CreateMap(int width, int height);

private:
  static Entity _CreateMapShell(int width, int height);       // basic map
  static void   _InitMap(Entity& map, int width, int height); // just a map (main parent
entity)
  */
protected:
};
