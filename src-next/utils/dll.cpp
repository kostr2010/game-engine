#include "./dll.hpp"
#include <iostream>

void* ImportDLL(std::string path) {
  path = "lib" + path + ".so";

  std::cout << "> {PATH} = <" << path.c_str() << ">\n";

  const char* c_path = path.c_str();

  /* on Linux, use "./myclass.so" */
  void* handle = dlopen("./libsystemHealth.so", RTLD_NOW);

  return handle;
}