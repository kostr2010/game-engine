// #include <cassert>
// #include <chrono>
// #include <thread>
// #include <vector>

// #include "../component/component.hpp"
// #include "../entity/entity.hpp"
// #include "../map/map.hpp"

// #include "../property/properties.hpp"
// #include "../property/property.hpp"

// #include "../system/system.hpp"
// #include "../system/systemManager.hpp"

// #include "../utils/assembly.hpp"
// #include "../utils/log.hpp"
// #include "../utils/vec2.hpp"

// #include <dlfcn.h>

// // ====================
// // Monitor
// // global manager for all managers

//   Monitor::Monitor() {
//     LOG_LVL_MONITOR_INIT("../log/monitor.log");

//     component_manager_ = ComponentManager{};
//     // TODO add try/catch here
//     LOG_LVL_MONITOR_ROUTINE("ComponentManager initialized");

//     entity_manager_ = EntityManager{};
//     // TODO add try/catch here
//     LOG_LVL_MONITOR_ROUTINE("EntityManager initialized");

//     system_manager_ = SystemManager{this};
//     // TODO add try/catch here
//     LOG_LVL_MONITOR_ROUTINE("SystemManager initialized");
//   }
//   Monitor::~Monitor() = default;

//   // wrappers for managers, so user has to speak only to monitor instead of directly to each one
//   of
//   // the managers

//   template <typename Component_t>
//   ComponentType Monitor::RegisterComponent() {
//     // if (component_manager_.Contains<Component_t>())
//     //   return component_manager_.GetComponentType<Component_t>();

//     ComponentType component = component_manager_.RegisterComponent<Component_t>();

//     // TODO add try/catch here
//     LOG_LVL_MONITOR_ROUTINE("component " << typeid(Component_t).name() << " registered with id "
//                                          << component);

//     return component;
//   }

//   template <typename Component_t>
//   void Monitor::AttachComponent(Component_t& component_new, EntityId entity) {
//     component_manager_.AttachComponent(entity, component_new);

//     Signature     signature_prev = entity_manager_.GetSignature(entity);
//     ComponentType component      = component_manager_.GetComponentType<Component_t>();

//     Signature signature_new = signature_prev.set(component, true);

//     UpdateSignature(entity, signature_new);

//     // TODO add try/catch here
//     LOG_LVL_MONITOR_ROUTINE("component " << typeid(Component_t).name() << " aka " << component
//                                          << " attached to entity " << entity
//                                          << ". now it's signature is "
//                                          << entity_manager_.GetSignature(entity));
//   }

//   template <typename Component_t>
//   void Monitor::RemoveComponent(EntityId entity) {
//     component_manager_.RemoveComponent<Component_t>(entity);

//     Signature     signature_prev = entity_manager_.GetSignature(entity);
//     ComponentType component      = component_manager_.GetComponentType<Component_t>();

//     Signature signature_new = signature_prev.set(component, false);

//     UpdateSignature(entity, signature_new);

//     // TODO add try/catch here
//     LOG_LVL_MONITOR_ROUTINE("component " << typeid(Component_t).name() << " aka " << component
//                                          << " removed from entity " << entity
//                                          << ". now it's signature is "
//                                          << entity_manager_.GetSignature(entity));
//   }

//   EntityId Monitor::AddEntity() {
//     EntityId entity_new = entity_manager_.CreateEntity();

//     // TODO add try/catch here
//     LOG_LVL_MONITOR_ROUTINE("new entity with id " << entity_new << " registered");

//     return entity_new;
//   }

//   void Monitor::RemoveEntity(EntityId entity) {
//     // std::cout << "  > start removing from entity manager\n";
//     entity_manager_.RemoveEntity(entity);
//     // std::cout << "  > start removing from component manager\n";
//     component_manager_.RemoveEntity(entity);
//     // std::cout << "  > start removing from system manager\n";
//     system_manager_.RemoveEntity(entity);
//     // std::cout << "  > removed from all systems\n";

//     // TODO add try/catch here
//     LOG_LVL_MONITOR_ROUTINE("entity " << entity << "deleted from all managers");
//   }

//   System* RegisterSystem(System* (*ctor)(Monitor*)) {
//     System* system = system_manager_.RegisterSystem(ctor);

//     // TODO add try/catch here
//     LOG_LVL_MONITOR_ROUTINE("new system " << system->GetMyOwnFuckingShittyId() << " registered");

//     return system;
//   }

//   System* GetSystem(std::string sys_name) {
//     return system_manager_.GetSystem(sys_name);
//   }

//   template <typename Component_t>
//   bool HasComponent(EntityId entity) {
//     return component_manager_.HasComponent<Component_t>(entity);
//   }

//   template <typename Component_t>
//   bool HasNoComponent(EntityId entity) {
//     return !HasComponent<Component_t>(entity);
//   }

//   template <typename Component_t>
//   Component_t* GetComponent(EntityId entity) {
//     return component_manager_.GetComponent<Component_t>(entity);
//   }

//   void AttachProperty(EntityId entity, PropertyType property) {
//     property_manager_.AttachProperty(entity, property);
//   }

//   void RemoveProperty(EntityId entity, PropertyType property) {
//     property_manager_.RemoveProperty(entity, property);
//   }

//   bool HasProperty(EntityId entity, PropertyType property) {
//     return property_manager_.HasProperty(entity, property);
//   }

//   bool HasNoProperty(EntityId entity, PropertyType property) {
//     return property_manager_.HasNoProperty(entity, property);
//   }

//   bool CheckIfEntityExists(EntityId entity) {
//     return entity_manager_.CheckIfEntityExists(entity);
//   }

//   void StartLoop() {
//     std::chrono::steady_clock::time_point begin_prev = std::chrono::steady_clock::now();

//     while (true) {
//       auto begin = std::chrono::steady_clock::now();
//       auto time_delta =
//           std::chrono::duration_cast<std::chrono::milliseconds>(begin - begin_prev).count();

//       // calling updaters
//       system_manager_.Update(time_delta);

//       auto end = std::chrono::steady_clock::now();

//       // std::cout << "I'm a dwarf and I'm digging the hole" << std::endl;

//       const int64_t LOOP_DURATION = 16; // 60fps
//       auto          time_elapsed =
//           std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
//       auto time_to_sleep = LOOP_DURATION - time_elapsed;

//       if (time_to_sleep > 0)
//         std::this_thread::sleep_for(std::chrono::milliseconds(time_to_sleep));

//       begin_prev = begin;
//     }
//   }

//   System* ImportSystem(std::string path) {
//     void* handle = ImportDLL(path);

//     SystemConstructor ctor = (SystemConstructor)dlsym(handle, "create_object");

//     System* system = (System*)ctor(this);
//     return system;
//   }

// private:
//   void* ImportDLL(std::string path) {
//     const char* c_path = path.c_str();

//     /* on Linux, use "./myclass.so" */
//     void* handle = dlopen(c_path, RTLD_LAZY);

//     return handle;
//   }

//   void UpdateSignature(EntityId entity, Signature& signature) {
//     // std::cout << "*\n" << std::endl;
//     entity_manager_.SetSignature(entity, signature);
//     // std::cout << "*\n" << std::endl;
//     system_manager_.UpdateEntitySignature(entity, signature);
//     // std::cout << "*\n" << std::endl;

//     // TODO add try/catch here
//     LOG_LVL_MONITOR_ROUTINE("entity's " << entity << " signature updated. now it's signature is "
//                                         << signature);
//   }

//   PropertyManager  property_manager_{};
//   ComponentManager component_manager_{};
//   EntityManager    entity_manager_{};
//   SystemManager    system_manager_{this};
// };
