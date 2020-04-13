#pragma once

// #include <chrono>
#include <ctime>
#include <fstream>

// ====================
// LVL_SYSTEM

#define LOG_LVL_SYSTEM_CLEAR()                                                                     \
  std::fstream log;                                                                                \
  log.open("log/system.log", std::ios::trunc | std::ios::out);                                     \
  log.close()

#define LOG_LVL_SYSTEM(system, msg)                                                                \
  std::fstream log;                                                                                \
  log.open("log/system.log", std::ios::app | std::ios::in);                                        \
  std::time_t result = std::time(nullptr);                                                         \
  log << std::asctime(std::localtime(&result)) << "[" << system << "] " << msg << std::endl;       \
  log.close()

// ====================
// LVL_COMPONENT
