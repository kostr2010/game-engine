#include "./component/components/health.hpp"
#include "./component/components/movement.hpp"
#include "./monitor/monitor.hpp"

// how shared_ptr works
// make_shared, shared_ptr
// static vs dynamic type, cast

int main() {
  Monitor monitor{};

  monitor.RegisterComponent<ComponentHealth>();
  monitor.RegisterComponent<ComponentMovement>();

  // auto SystemCombat = monitor.RegisterSystem<SystemCombat>();

  return 0;
}