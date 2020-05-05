#pragma once

#include <chrono>
#include <cstring>
#include <functional>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "../system.hpp"
#include "systemKick.hpp"
#include "systemTerrain.hpp"

/*
input types:

1. system <SYSTEM_NAME> do <FUNC_NAME> <ARG1> <ARG2> ... <ARGN>
2. monitor <COMMAND_NAME> <ENTITY_ID>
*/

class SystemConsole : public System {
public:
  SystemConsole(Monitor* monitor) : System(monitor) {
  }

  ~SystemConsole() = default;

  ResponseCode Init() override {
    fcntl(0, F_SETFL, (fcntl(0, F_GETFL) | O_NONBLOCK));

    return ResponseCode::Success;
  }

  ResponseCode Update(long time_delta) {
    char buf[50];

    auto begin = std::chrono::steady_clock::now();
    int  res   = read(0, buf, 50);
    auto end   = std::chrono::steady_clock::now();
    auto delta = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();

    std::string input{buf};

    auto index = input.find('\n');
    if (index == std::string::npos)
      return ResponseCode::Failure;
    else {
      auto input_no_eof = input.substr(0, index);
      std::cout << GetLine(input_no_eof) << std::endl;
      return ResponseCode::Success;
    }
  }

  const char* GetLine(std::string line) {
    std::vector<std::string> arr = split(line, " ");

    if (arr.size() == 0)
      return "invalid input";

    // TODO: assert for 0 chunks
    auto command = arr[0];
    auto args    = std::vector<std::string>(arr.begin() + 1, arr.end());

    if (map_namespaces.find(command) == map_namespaces.end())
      return "no such command found";

    auto handler = map_namespaces[command];

    handler(args);
    return "done";
  }

  void RegisterDependencies() {
  }

  std::vector<ComponentType> GetRequiredComponentTypes() {
    return {};
  }

private:
  typedef std::map<std::string, std::function<void(std::vector<std::string>)>> Router;

  Router map_namespaces{
      {"monitor", [this](std::vector<std::string> args) {
         // body
         Router map_commands{
             {"reg_sys",
              [&](std::vector<std::string> args) {
                // body
                auto system_name = args[0];

                Router map_systems{{"SystemTerrain",
                                    [&](std::vector<std::string> args) {
                                      // body
                                      this->monitor_->RegisterSystem<SystemTerrain>();
                                      std::cout << "Terrain registered" << std::endl;
                                    }},
                                   {"SystemKick", [&](std::vector<std::string> args) {
                                      // body
                                      this->monitor_->RegisterSystem<SystemKick>();
                                      std::cout << "Kick registered" << std::endl;
                                    }}};

                auto root     = args[0];
                auto args_new = std::vector<std::string>(args.begin() + 1, args.end());

                map_systems[root](args_new);
              }},
             {"reg_comp", [&](std::vector<std::string> args) {
                // body
                auto system_name = args[0];

                Router map_systems{{"SystemTerrain",
                                    [&](std::vector<std::string> args) {
                                      // body
                                      this->monitor_->RegisterSystem<SystemTerrain>();
                                    }},
                                   {"SystemKick", [&](std::vector<std::string> args) {
                                      // body
                                      this->monitor_->RegisterSystem<SystemKick>();
                                    }}};
                auto   root     = args[0];
                auto   args_new = std::vector<std::string>(args.begin() + 1, args.end());

                map_systems[root](args_new);
              }}};

         auto root     = args[0];
         auto args_new = std::vector<std::string>(args.begin() + 1, args.end());

         map_commands[root](args_new);
       }}};

  // monitor import SystemTerrain
  // monitor reg_sys SystemTerrain

  // std::map<std::string, const char* (*)(std::vector<std::string>)>

  std::vector<std::string> split(const std::string& str, const std::string& delim) {
    std::vector<std::string> tokens;
    size_t                   prev = 0, pos = 0;

    do {
      pos = str.find(delim, prev);

      if (pos == std::string::npos)
        pos = str.length();

      std::string token = str.substr(prev, pos - prev);

      if (!token.empty())
        tokens.push_back(token);

      prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());

    return tokens;
  }
};
