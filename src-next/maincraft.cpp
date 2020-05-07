#include "./monitor/monitor.hpp"
#include "./utils/log.hpp"

#include <iostream>
#include <string>

int main() {
  Monitor monitor{};

  monitor.GetSystemConstructor("./system/systems/systemDynamic/systemHealth.so");
}