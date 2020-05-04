#pragma once

#include <chrono>
#include <cstring>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "../system.hpp"

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

  //   ResponseCode Input() {
  //     std::thread t1(startInputHandling);

  //     return ResponseCode::Success;
  //   }

  //   void startInputHandling() {
  //     while (true) {
  //       std::string input;
  //       std::getline(std::cin, input);

  //       std::lock_guard<std::mutex> guard(messages_mutex);

  //       messages.push_back(input);
  //     }
  //   }

  ResponseCode Update(long time_delta) {
    fcntl(0, F_SETFL, (fcntl(0, F_GETFL) | O_NONBLOCK));

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

    if (handlers.find(command) == handlers.end())
      return "no such command found";

    auto handler = handlers[command];
    return handler(args);
  }

  void RegisterDependencies() {
  }

  std::vector<ComponentType> GetRequiredComponentTypes() {
    return {};
  }

private:
  std::map<std::string, const char* (*)(std::vector<std::string>)> handlers{
      {std::string("monitor"), [](std::vector<std::string>) { return "done"; }},
      {std::string("system"), [](std::vector<std::string>) { return "done"; }},
  };

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
