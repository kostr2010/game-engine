#pragma once

// #include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <sstream>

// #ifndef LOG_LVL_SYSTEM_
// #define LOG_LVL_SYSTEM_
extern std::fstream log_system;
extern const char*  log_system_path;
// #endif
// #ifndef LOG_LVL_COMPONENT_
// #define LOG_LVL_COMPONENT_
extern std::fstream log_component;
extern const char*  log_component_path;
// #endif

// #ifndef LOG_LVL_ENTITY_
// #define LOG_LVL_ENTITY_
extern std::fstream log_entity;
extern const char*  log_entity_path;
// #endif

// #ifndef TIMESTAMP
// #define TIMESTAMP
extern std::time_t result;
// #endif

// #ifndef BUF
// #define BUF
extern std::ostringstream buf;
// #endif

// ====================
// LVL_SYSTEM

#define LOG_LVL_SYSTEM_INIT()                                                                      \
  log_system.open(log_system_path, std::ios::trunc | std::ios::out);                               \
  log_system.close()

#define LOG_LVL_SYSTEM_ROUTINE(system, msg)                                                        \
  log_system.open(log_system_path, std::ios::app | std::ios::in);                                  \
  /* result = std::time(nullptr); */                                                               \
  buf << "[" << system << "]";                                                                     \
  log_system /* << std::asctime(std::localtime(&result))*/ << std::setw(31) << std::left           \
                                                           << buf.str() << msg << std::endl;       \
  buf.str(std::string());                                                                          \
  log_system.close()

#define LOG_LVL_SYSTEM_FAILURE(system, msg)                                                        \
  log_system.open(log_system_path, std::ios::app | std::ios::in);                                  \
  /* result = std::time(nullptr); */                                                               \
  buf << "[" << system << "]";                                                                     \
  log_system /* << std::asctime(std::localtime(&result))*/                                         \
      << std::setw(20) << std::left << buf.str() << std::setw(11) << " {FAILURE} " << msg          \
      << std::endl;                                                                                \
  buf.str(std::string());                                                                          \
  log_system.close()

// ====================
// LVL_COMPONENT

#define LOG_LVL_COMPONENT_INIT()                                                                   \
  log_component.open(log_component_path, std::ios::trunc | std::ios::out);                         \
  log_component.close()

#define LOG_LVL_COMPONENT_ROUTINE(msg)                                                             \
  log_component.open(log_component_path, std::ios::app | std::ios::in);                            \
  /*result = std::time(nullptr);*/                                                                 \
  log_component /*<< std::asctime(std::localtime(&result))*/ << std::setw(31) << std::left         \
                                                             << "[ComponentManager]" << msg        \
                                                             << std::endl;                         \
  buf.str(std::string());                                                                          \
  log_component.close()

#define LOG_LVL_COMPONENT_FAILURE(msg)                                                             \
  log_component.open(log_component_path, std::ios::app | std::ios::in);                            \
  /* result = std::time(nullptr); */                                                               \
  log_component /* << std::asctime(std::localtime(&result))*/                                      \
      << std::setw(20) << std::left << "[ComponentManager]" << std::setw(11) << " {FAILURE} "      \
      << msg << std::endl;                                                                         \
  buf.str(std::string());                                                                          \
  log_component.close()

// ====================
// LVL_ENTITY

#define LOG_LVL_ENTITY_INIT()                                                                      \
  log_entity.open(log_entity_path, std::ios::trunc | std::ios::out);                               \
  log_entity.close()

#define LOG_LVL_ENTITY_ROUTINE(msg)                                                                \
  log_entity.open(log_entity_path, std::ios::app | std::ios::in);                                  \
  /*result = std::time(nullptr);*/                                                                 \
  log_entity /*<< std::asctime(std::localtime(&result))*/ << std::setw(31) << std::left            \
                                                          << "[EntityManager]" << msg              \
                                                          << std::endl;                            \
  buf.str(std::string());                                                                          \
  log_entity.close()

#define LOG_LVL_ENTITY_FAILURE(msg)                                                                \
  log_entity.open(log_entity_path, std::ios::app | std::ios::in);                                  \
  /* result = std::time(nullptr); */                                                               \
  log_entity /* << std::asctime(std::localtime(&result))*/                                         \
      << std::setw(20) << std::left << "[EntityManager]" << std::setw(11) << " {FAILURE} " << msg  \
      << std::endl;                                                                                \
  buf.str(std::string());                                                                          \
  log_entity.close()
