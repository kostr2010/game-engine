g++ -fPIC -shared sysDin.cpp -o sysDin.so
g++ class_user.cpp -ldl -o class_user