#pragma once

typedef int Property;

class PropertyManager {
public:
  PropertyManager()  = default;
  ~PropertyManager() = default;

  Property RegisterProperty();

private:
};