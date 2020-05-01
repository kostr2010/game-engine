#pragma once

#include "../../../component/components/controllable.hpp"
#include "../../../component/components/movement.hpp"
#include "../../../component/components/position.hpp"
#include "../system.hpp"
#include "../systemInput.hpp"

#include <vector>

class SystemControllerMovement : public System {
public:
  SystemControllerMovement(Monitor* monitor) : System(monitor) {
  }

  ResponseCode Init() override {
    SystemInputConsole* sys_input = monitor_->GetSystem<SystemInputConsole>();
    // sys_input->AddCallback("SystemControllerMovement", [MoveBy](EventInputConsole
    // event){MoveBy(event)});

    return ResponseCode::Success;
  }

  std::vector<ComponentType> GetRequiredComponentTypes() override {
    return {monitor_->RegisterComponent<ComponentControllable>(),
            monitor_->RegisterComponent<ComponentPosition>(),
            monitor_->RegisterComponent<ComponentMovement>()};
  }

  void RegisterDependencies() override {
    monitor_->RegisterSystem<SystemInputConsole>();
  }

private:
  void MoveBy(EventInputConsole event) {
  }
};