#pragma once

#include <chrono>
#include <ctime>
#include <fstream>

#define LOG_LVL_SYSTEM(system, msg)                                                                \
  std::fstream log;                                                                                \
  log.open("log/system_log.log", std::ios::app | std::ios::in);                                    \
  std::time_t result = std::time(nullptr);                                                         \
  log << std::asctime(std::localtime(&result)) << "[" << system << "] " << msg << std::endl;       \
  log.close()
