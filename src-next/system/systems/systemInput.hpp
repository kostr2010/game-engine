#pragma once

#include "../system.hpp"
#include "./systemMovement.hpp"

#include <map>

enum class Keys {
  A,
  S,
  W,
  D,
  E,
  LMB,
  RMB,
};

class SystemInput : public System {
public:
  SystemInput(Monitor* monitor) : System(monitor) {
  }

  ~SystemInput() = default;

  ResponseCode AddCallback(const char* key, void (*function)()) {
    if (callbacks_.find(key) == callbacks_.end())
      return ResponseCode::Failure;

    callbacks_[key] = function;

    return ResponseCode::Success;
  }

  ResponseCode RemoveCallback(const char* key) {
    if (callbacks_.find(key) == callbacks_.end())
      return ResponseCode::Failure;

    callbacks_.erase(key);

    return ResponseCode::Success;
  }

  std::vector<ComponentType> GetRequiredComponentTypes() override {
    // return {monitor_->RegisterComponent<ComponentMovement>()};
    return {};
  }

  void RegisterDependentSystems() override {
    // monitor_->RegisterSystem<SystemTerrain>();
  }

private:
  std::map<const char*, void (*)()> callbacks_;
};