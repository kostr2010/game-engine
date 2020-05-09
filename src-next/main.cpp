#include "./system/systemManager.hpp"

#include <iostream>
#include <string>

// TO GOOGLE
// [-] кд дерево
// [?] stackoverflow.com/questions/400257/how-can-i-pass-a-class-member-function-as-a-callback

// FOR NEXT TIME
// [-] UI thread to read console commands
// [-] (type2*)(type1*) -> static / dynamic cast
// [-] read / write from / to disc (serialization)
// [-] make spawner - smth that calls factory and checks needed conditions & requirements

// DONE
// [+] padding
// [+] movement
// [+] virtual destructor, where and why -> effective c++ #1
// [+] how shared_ptr works
// [+] make_shared, shared_ptr
// [+] static vs dynamic type, cast
// [+] !!! unique_ptr
// [+] add response codes
// [+] get rid of booleans in components (! new bitmap and manager)
// [+] deactivate instead of delete

int main() {
  std::cout << "start" << std::endl;

  SystemManager sys_man{};
  sys_man.ImportSystem("systemGameZero");

  return 0;
}
