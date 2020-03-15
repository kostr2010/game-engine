#include "./model.hpp"
#include <vector>

// SUMMARY of women day:
// + AbilityResult - piece of shit which contains result of an ability execution and the entity
// snapshots
// + ability execution response system - each ability applying returns AbilityResult
// + AbilityResult can be used by UI to produce step-by-step animations and reproduce what has
// happened
// + each dispatcher is wrapped by Entity.Apply or Map.ApplyAbility for auto-producing snapshots for
// entity_before and entity_after
// + void AnimationFunction(Entity entity_before, Entity entity_after, EventType event_type)
// + EventType describes what happened with the Entity after the Ability applying

// + Map initilaizes by vector<Tile> where Tile is Tile with nullptr and actors and object with
// nullptrs same way
// + Map must assign itself to each provided Tile or Object or Actor
// + Map must provide way to get an entity by "path" - sequence of "pointers" which discribes a path
// through Map objects tree
// + UI gets Map snapshot as initial data with generated path for each entity (startup)

// NEXT BIG THINGS:
// - Entity.path exists
// - Entity.GeneratePath realization
// - Map.GetEntity realization
// - Map.ApplyAbility realization
// - develop an example of game scene

// UI
// f1.1 idle - draw idle animation/sprite with entity params extracted from abilities
// f2.2 acting - animation of changing something (linear param changing). from state_before to
// state_after with change_type f2.2.1. it erases acting tile totally f2.2.2. get someway acting
// duration f2.2.3. perform preset animation or linear animation (movement) if preset is missing

// 1. initialize model (load config from file or generate a new one)
// 2. get model (Map object)
// 3. initial rendering - execute f1.1 for each tile and its direct children
// 4. start game loop
// 5. wait for ui user input
// 6. apply an ability for entity_origin and entity_target and get an ability_result with an array
// of sub_results
// 7. draw each level of an ability_results
// 7.1 execute f2.2 on each ability_result of current level

// UI 2
// - ui has an array of levels where each level is an array of GraphicalInstnce where
// GraphicalInstance is a class with such fields:
//      - entity_from
//      - entity_current *is temporary for each getActualView call*
//      - entity_to
//      - change_type *is a processor key for a processor which provide changing from entity_from to
//        entity_to and stores result at entity_current*
//      - animation_duration
//      - animation_time_past
//      - animation_frames *is a list of frames where each frame is an image*
//      - getActualView(timeDelta: number) => Image *uses change_type and entity_current*

// for example:
// we have Ball_start with x = 0
// and Ball_end with x = 10
// and change_type = Roll
// (change_type is enum)
// each getActualView call processor does linear changing of Ball_start -> Ball_current
// animation_phase = animation_time_past / animation_duration
// get animation_kind by processing Ball_current through "decider"
// (animation_kind is enum)
// animation_frames are provided by change_type key from AnimationsMap -
// AnimationsMap[change_type][animation_kind] animation_frames + animation_phase +
// Ball_current.position = current_frame (absolutely positioned)

int main() {
    EntityActive character1 = EntityFactoryActive::CreateWarrior();
    EntityActive character2 = EntityFactoryActive::CreateWarrior();
    EntityActive character3 = EntityFactoryActive::CreateWarrior();

    // map.ApplyAbilty(ch1, ch2, Kick);

    Entity obj1 = EntityFactory::CreateThing();
    Entity obj2 = EntityFactory::CreateThing();
    Entity obj3 = EntityFactory::CreateThing();
    Entity obj4 = EntityFactory::CreateThing();

    std::vector<Tile> tiles = {
        Tile(nullptr, {obj1}, {character1}), // 0:0
        Tile(nullptr, {}, {character2}),     // 0:1
        Tile(nullptr, {}, {}),               // 0:2
        Tile(nullptr, {}, {}),               // 1:0
        Tile(nullptr,
             {
                 obj2,
                 obj3,
             },
             {}),                            // 1:1
        Tile(nullptr, {}, {}),               // 1:2
        Tile(nullptr, {}, {}),               // 2:0
        Tile(nullptr, {}, {}),               // 2:1
        Tile(nullptr, {}, {}),               // 2:2
        Tile(nullptr, {}, {}),               // 3:0
        Tile(nullptr, {obj4}, {character3}), // 3:1
        Tile(nullptr, {}, {}),               // 3:2
        Tile(nullptr, {}, {}),               // 4:0
        Tile(nullptr, {}, {}),               // 4:1
        Tile(nullptr, {}, {}),               // 4:2
    };

    Map world_map(tiles, 5, 3);

    // world_map.ApplyAbility();
}