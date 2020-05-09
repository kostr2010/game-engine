#include "./log.hpp"

std::fstream log_system;
const char* log_system_path = "/home/dominator/shitcodes/c-c++/kt/sem-4/game-engine/log/system.log";

std::fstream log_component;
const char*  log_component_path =
    "/home/dominator/shitcodes/c-c++/kt/sem-4/game-engine/log/component.log";

std::fstream log_entity;
const char* log_entity_path = "/home/dominator/shitcodes/c-c++/kt/sem-4/game-engine/log/entity.log";

std::time_t result = std::time(nullptr);

std::ostringstream buf;
