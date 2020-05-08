#pragma once

#include "../system.hpp"
#include "./systemMovement.hpp"

#include <map>

enum class KeyboardKey {
  A,
  S,
  W,
  D,
  E,
  LMB,
  RMB,
};

struct EventInputConsole {
  KeyboardKey key;
};

class SystemInputConsole : public System {
public:
  SystemInputConsole(Monitor* monitor) : System(monitor) {
  }

  ~SystemInputConsole() = default;

  ResponseCode Input() {
  }

  ResponseCode AddCallback(const char* key, void (*function)(EventInputConsole event)) {
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

  std::vector<ComponentTypeGlobal> GetRequiredComponentTypes() override {
    // return {monitor_->RegisterComponent<ComponentMovement>()};
    return {};
  }

  void RegisterDependencies() override {
    // monitor_->RegisterSystem<SystemTerrain>();
  }

private:
  std::map<const char*, void (*)(EventInputConsole event)> callbacks_;
};
