#include "./health.hpp"
#include "../componentInfo.hpp"

extern "C" ComponentInfo get_component_info() {
  return ComponentInfo{.comp_size = sizeof(ComponentHealth),
                       .comp_type = std::string("ComponentHealth")};
}