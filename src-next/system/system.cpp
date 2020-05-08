#include "./system.hpp"

System::System(SystemManager* sys_man) {
  system_manager_ = sys_man;
}

ResponseCode System::Init() {
  return ResponseCode::Success;
};

ResponseCode System::Update(int64_t time_delta) {
  return ResponseCode::Success;
}