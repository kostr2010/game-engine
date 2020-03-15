#pragma once

#include <vector>
#include "../entity/entity.hpp"
#include "../map/map.hpp"

class Tile {
  public:
    Tile(Map* world_map, const std::vector<Entity>& objects,
         const std::vector<EntityActive>& actors,
         const EffectKind&                surface_effect = EffectKind::Neutral,
         const int surface_effect_strength = 0, const int surface_effect_duration = 0);
    ~Tile() = default;

    void ObjectsAdd(const Entity& object);
    void ObjectsRemove(const Entity& object);

    void ActorsAdd(const EntityActive& actor);
    void ActorsRemove(const EntityActive& actor);

    void SetMap(Map* world_map);

    Coord      Coord_;
    EffectKind surface_effect_;
    int        surface_effect_strength_;
    int        surface_effect_duration_;

  private:
    std::vector<Entity>       objects_;
    std::vector<EntityActive> actors_;

    Map* world_map_;

  protected:
};