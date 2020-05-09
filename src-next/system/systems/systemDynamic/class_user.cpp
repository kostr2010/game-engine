// #include "myclass.h"
#include "sysDin.hpp"
#include <dlfcn.h>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
  /* on Linux, use "./myclass.so" */
  // void* handle = dlopen("./system/systems/systemDynamic/sysDin.so", RTLD_LAZY);
  void* handle = dlopen("./system/systems/systemDynamic/libsystemHealth.so", RTLD_LAZY);

  cout << handle << endl;
  cout << dlerror() << endl;

  //   MyClass* (*create)();
  //   void (*destroy)(MyClass*);

  //   create  = (MyClass * (*)()) dlsym(handle, "create_object");
  //   destroy = (void (*)(MyClass*))dlsym(handle, "destroy_object");

  //   MyClass* myClass = (MyClass*)create();
  //   myClass->DoSomething();
  //   destroy(myClass);
}