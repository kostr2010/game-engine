#pragma once

#include "engine-types.h"

//====================
// CONSTANTS

std::map<AbilityKind, std::function<void(Entity& origin, Entity& target)>> dict_ability_dispatcher = {
    {Health, [](Entity& origin, Entity& target) -> void {
            return;
        }
    },

    {Kick, [](Entity& origin, Entity& target) -> void {
            if (origin.abilities_.count(Kick) != 0) {
                Ability target_ability = target.abilities_[Health];                         

                double damage_amount = origin.abilities_[Kick].GetStateValue(DamageAmount); 
                double hp_was = target_ability.GetStateValue(HpCurrent);
                double hp_now = hp_was - damage_amount;

                target_ability.SetStateValue(HpCurrent, hp_now);

                target.abilities_[Health] = target_ability;
            }                      
        }
    },
};
