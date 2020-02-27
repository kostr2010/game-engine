#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <map>

#include "engine-types.h"

using namespace std;

int main() {
    Entity ch1 = EntityFactory::CreateWarrior();
    Entity ch2 = EntityFactory::CreateWarrior();

    ch1.Apply(CanKick, ch2);
    
    cout << "ch2: \n" << ch2;
}
