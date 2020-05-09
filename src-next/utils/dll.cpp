#include "./dll.hpp"
#include <iostream>

void* ImportDLL(std::string path) {
  path = "../dll/lib" + path + ".so";
  // ./system/systems/systemDynamic/lib
  std::cout << "> {PATH} = <" << path.c_str() << ">\n";

  const char* c_path = path.c_str();

  /* on Linux, use "./myclass.so" */
  void* handle = dlopen(c_path, RTLD_NOW);

  // std::cout << "> {DLERROR}" << dlerror() << std::endl;
  std::cout << "> {HANDLER} " << handle << std::endl;

  return handle;
}