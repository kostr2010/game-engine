#pragma once

#include <dlfcn.h>
#include <string>

void* ImportDLL(std::string path) {
  const char* c_path = path.c_str();

  /* on Linux, use "./myclass.so" */
  void* handle = dlopen(c_path, RTLD_LAZY);

  return handle;
}