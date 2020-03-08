#include "tile.hpp"
#include <algorithm>

Tile::Tile(Map* world_map, const std::vector<Entity>& objects,
           const std::vector<EntityActive>& actors,
           const EffectKind&                surface_effect = EffectKind::Neutral,
           const int surface_effect_strength = 0, const int surface_effect_duration = 0) {
  world_map_ = world_map;
  objects_   = objects;
  actors_    = actors;
  // Coord_     = Coord;

  surface_effect_          = surface_effect;
  surface_effect_duration_ = surface_effect_duration;
  surface_effect_strength_ - surface_effect_strength;
}

void Tile::ObjectsAdd(const Entity& object) {
  // FIXME check if has multiple objects
  objects_.push_back(object);
}

void Tile::ObjectsRemove(const Entity& object) {
  objects_.erase(std::remove_if(objects_.begin(), objects_.end(), [object](const Entity& object_) {
    return object == object_;
  }));
}

void Tile::ActorsAdd(const EntityActive& actor) {
  if (actors_.size() == 0)
    actors_.push_back(actor);
  else
    // FIXME throw exception
    return;
}

void Tile::ActorsRemove(const EntityActive& actor) {
  actors_.erase(std::remove_if(
      actors_.begin(), actors_.end(), [actor](const Entity& actor_) { return actor == actor_; }));
}

void Tile::SetMap(Map* world_map) {
  world_map_ = world_map;
}