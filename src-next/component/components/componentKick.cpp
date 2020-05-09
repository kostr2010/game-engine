#include "./componentKick.hpp"
#include "../componentInfo.hpp"

extern "C" ComponentInfo get_component_info() {
  return ComponentInfo{.comp_size = sizeof(ComponentKick),
                       .comp_type = std::string("componentKick")};
}
