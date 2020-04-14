#pragma once

// #include <chrono>
#include <ctime>
#include <fstream>

#ifndef LOG_LVL_SYSTEM_
std::fstream log_system;
#endif

#ifndef LOG_LVL_MONITOR_
std::fstream log_monitor;
#endif

// ====================
// LVL_SYSTEM

#define LOG_LVL_SYSTEM_INIT()                                                                      \
  log_system.open("log/system.log", std::ios::trunc | std::ios::out);                              \
  log_system.close()

#define LOG_LVL_SYSTEM(system, msg)                                                                \
  log_system.open("log/system.log", std::ios::app | std::ios::in);                                 \
  /*std::time_t result = std::time(nullptr); */                                                    \
  log_system /* << std::asctime(std::localtime(&result))*/ << "[" << typeid(system).name() << "] " \
                                                           << msg << std::endl;                    \
  log_system.close()

// ====================
// LVL_MONITOR

#define LOG_LVL_MONITOR_INIT()                                                                     \
  /*std::fstream log_monitor;*/                                                                    \
  log_monitor.open("log/monitor.log", std::ios::trunc | std::ios::out);                            \
  log_monitor.close()

#define LOG_LVL_MONITOR(msg)                                                                       \
  log_monitor.open("log/monitor.log", std::ios::app | std::ios::in);                               \
  /*std::time_t result = std::time(nullptr);*/                                                     \
  log_monitor /*<< std::asctime(std::localtime(&result))*/ << "[Monitor] " << msg << std::endl;    \
  log_monitor.close()
