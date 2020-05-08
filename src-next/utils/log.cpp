#include "./log.hpp"

std::fstream log_system;
const char*  log_system_path;

std::fstream log_component;
const char*  log_component_path;

std::fstream log_entity;
const char*  log_entity_path;

std::time_t result = std::time(nullptr);

std::ostringstream buf;
