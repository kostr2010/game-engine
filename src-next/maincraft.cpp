#include "./monitor/monitor.hpp"
#include "./utils/log.hpp"

#include <iostream>
#include <string>

int main() {
  Monitor monitor{};

  monitor.ImportSystem("./system/systems/systemDynamic/systemHealth.so");
}