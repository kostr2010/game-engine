#pragma once

#include <bitset>
#include <cassert>
#include <map>

#include "../entity/entity.hpp"
#include "../utils/assembly.hpp"
#include "./properties.hpp"

typedef int Property;

const int MAX_PROPERTIES = 100;

class PropertyManager {
public:
  PropertyManager()  = default;
  ~PropertyManager() = default;

  // Property RegisterProperty() {
  //   assertm(property_next_ > MAX_PROPERTIES, "max properties reached");

  //   return property_next_++;
  // }

  bool HasProperty(Entity entity, PropertyType property) {
    return properties_[entity][property];
  }

  bool HasNoProperty(Entity entity, PropertyType property) {
    return !HasProperty(entity, property);
  }

  void SetProperty(Entity entity, PropertyType property, bool value) {
    properties_[entity][property] = value;
  }

  void AttachProperty(Entity entity, PropertyType property) {
    SetProperty(entity, property, true);
  }

  void RemoveProperty(Entity entity, PropertyType property) {
    SetProperty(entity, property, false);
  }

private:
  std::map<Entity, std::bitset<MAX_PROPERTIES>> properties_;

  Property property_next_ = 0;
};