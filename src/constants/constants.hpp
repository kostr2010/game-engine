#pragma once

#include "../main-classes/main-classes.hpp"
#include <map>

std::map<AbilityKind, std::function<void(Entity& origin, Entity& target)>> dict_ability_dispatcher;
