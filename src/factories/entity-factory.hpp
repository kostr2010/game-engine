#pragma once
#include <cstdio>

#include "../main-classes/main-classes.hpp"

// class Entity;
// class Coordinates;

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
    static Entity CreateChest(Entity* parent, size_t lock_lvl, const std::vector<Entity>& subentites = {});

    // items
    static Entity CreateFood(Entity* parent);

    // misc
    static Entity CreateTile(Entity* parent, int pos_x, int pos_y,
                             int walkability_level);                 // tile (only tile may be a subentity of a map) <- how to check?
    static Entity CreateMapShell();                                  // basic map
    static Entity InitMap(Entity* map, size_t width, size_t height); // just a map (main parent entity)

  private:
  protected:
};
