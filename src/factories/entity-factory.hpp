#pragma once

//===================
// ENUMS

enum EntityKind {
    // heroes
    Warrior,
    // enemies
    Mimic,
    // containers
    Chest,
    // items
    Food,
    // misc
    Map,
    Tile,
};

//===================
// CLASSES DECLARATION

//====================
// entity factory

class EntityFactory {
    // entity inherits parent's coordinateson every level below tile
    // (tiles being the first layer to have individual coordinates)
  public:
    // map shell
    static Entity CreateMapShell();

    // just a map (main parent entity)
    static Entity InitMap(Entity* map, size_t width, size_t height);

    // tile (only tile may be a subentity of a map) <- how to check?
    static Entity CreateTile(Entity* parent, Coordinates pos, int WalkableLevel);

    // playable characters
    static Entity CreateWarrior(Entity* parent);

    // objects
    static Entity CreateChest(Entity* parent, size_t capacity, size_t lock_lvl);

    // enemies
    static Entity CreateMimic(Entity* parent);

    // items
    static Entity CreateFood(Entity* parent);

  private:
  protected:
};
