#pragma once

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "../ability/ability.hpp"
#include "../constants/engine-constants.hpp"

//====================
// CLASSES DECLARATION

class Coordinates {
  public:
    Coordinates(int x = 0, int y = 0);

    int  GetX();
    int  GetY();
    void SetCoordinates(int x_new, int y_new);

  private:
    int x_, y_;

  protected:
};

class Entity {
  public:
    Entity(Entity* parent, std::vector<Ability> abilities = {}, std::vector<Entity> subentities = {}, Coordinates coordinates = {});

    void   Apply(AbilityKind kind, Entity& target);
    int    GetSubEntitiesCount();
    void   AddSubentity(std::vector<Entity> items);
    void   RemoveSubentity(size_t index);
    Entity GetSubentity(size_t index);

    friend std::ostream& operator<<(std::ostream& stream, Entity entity);

    std::map<AbilityKind, Ability> abilities_;
    Coordinates                    coordinates_;
    Entity*                        parent_;

  private:
    std::vector<Entity> subentities_;

  protected:
};

class EntityFactory {
  public:
    // just a map (main parent entity)
    static Entity CreateMap(size_t width, size_t height);

    // tile (only tile may be a subentity of a map)
    static Entity CreateTile(Entity* parent);

    // playable characters
    static Entity CreateWarrior(Entity* parent);
    static Entity CreateMage(Entity* parent);
    static Entity CreateCustom(Entity* parent);

    // objects
    static Entity CreateChest(Entity* parent, size_t capacity, size_t lock_lvl);

    // enemies
    static Entity CreateMimic(Entity* parent);

    // items
    static Entity CreateFood(Entity* parent);

  private:
  protected:
};

class EntityController {
  public:
    static Entity GetSubentityMap(Entity world_map, size_t x, size_t y);
};