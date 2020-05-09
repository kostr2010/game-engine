#ifndef __SYS_DIN__
#define __SYS_DIN__

// class MyClass {
// public:
//   MyClass();

//   /* use virtual otherwise linker will try to perform static linkage */
//   virtual void DoSomething();

// private:
//   int x;
// };

#include "../../../component/components/health.hpp"
#include "../../../utils/log.hpp"
#include "../../system.hpp"

class SystemHealth : public System {
public:
  SystemHealth() = delete;

  SystemHealth(SystemManager* sys_man);

  ResponseCode ChangeCurrentHp(EntityId entity, int delta);

  ResponseCode ChangeMaximumHP(EntityId entity, int delta);

  std::vector<SystemName> GetDependentSystemNames() override;

  std::vector<ComponentTypeGlobal> GetDependentComponentTypes() override;

  std::vector<ComponentTypeGlobal> GetRequiredComponentTypes() override;

  std::string GetMyOwnFuckingShittyId() override;
};

#endif