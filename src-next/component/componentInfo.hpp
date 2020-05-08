#pragma once

#include <cstddef>
#include <string>

struct ComponentInfo {
  size_t      comp_size;
  std::string comp_type; // TODO: do smth with that?
};

typedef ComponentInfo (*GetComponentInfo)();