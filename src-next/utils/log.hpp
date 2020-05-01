#pragma once

// #include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>

#ifndef LOG_LVL_SYSTEM_
#define LOG_LVL_SYSTEM_
std::fstream log_system;
const char*  log_system_path;
#endif

#ifndef LOG_LVL_MONITOR_
#define LOG_LVL_MONITOR_
std::fstream log_monitor;
const char*  log_monitor_path;
#endif

#ifndef LOG_LVL_COMPONENT_
#define LOG_LVL_COMPONENT_
std::fstream log_component;
const char*  log_component_path;
#endif

#ifndef TIMESTAMP
#define TIMESTAMP
std::time_t result = std::time(nullptr);
#endif

// ====================
// LVL_SYSTEM

#define LOG_LVL_SYSTEM_INIT(path)                                                                  \
  log_system_path = path;                                                                          \
  log_system.open(log_system_path, std::ios::trunc | std::ios::out);                               \
  log_system.close()

#define LOG_LVL_SYSTEM_ROUTINE(system, msg)                                                        \
  log_system.open(log_system_path, std::ios::app | std::ios::in);                                  \
  /* result = std::time(nullptr); */                                                               \
  log_system /* << std::asctime(std::localtime(&result))*/ << "[" << std::setw(16) << std::left    \
                                                           << typeid(system).name() << "] " << msg \
                                                           << std::endl;                           \
  log_system.close()

#define LOG_LVL_SYSTEM_FAILURE(system, msg)                                                        \
  log_system.open(log_system_path, std::ios::app | std::ios::in);                                  \
  /* result = std::time(nullptr); */                                                               \
  log_system /* << std::asctime(std::localtime(&result))*/                                         \
      << "[" << std::setw(16) << std::left << typeid(system).name() << "] "                        \
      << "{FAILURE} " << msg << std::endl;                                                         \
  log_system.close()

// ====================
// LVL_MONITOR

#define LOG_LVL_MONITOR_INIT(path)                                                                 \
  log_monitor_path = path;                                                                         \
  log_monitor.open(log_monitor_path, std::ios::trunc | std::ios::out);                             \
  log_monitor.close()

#define LOG_LVL_MONITOR_ROUTINE(msg)                                                               \
  log_monitor.open(log_monitor_path, std::ios::app | std::ios::in);                                \
  /*result = std::time(nullptr);*/                                                                 \
  log_monitor /*<< std::asctime(std::localtime(&result))*/                                         \
      << "[Monitor] " << msg << std::endl;                                                         \
  log_monitor.close()

// ====================
// LVL_COMPONENT

#define LOG_LVL_COMPONENT_INIT(path)                                                               \
  log_component_path = path;                                                                       \
  log_component.open(log_component_path, std::ios::trunc | std::ios::out);                         \
  log_component.close()

#define LOG_LVL_COMPONENT_ROUTINE(component, msg)                                                  \
  log_component.open(log_component_path, std::ios::app | std::ios::in);                            \
  /*result = std::time(nullptr);*/                                                                 \
  log_component /*<< std::asctime(std::localtime(&result))*/ << "[" << typeid(component).name()    \
                                                             << "] " << msg << std::endl;          \
  log_component.close()
