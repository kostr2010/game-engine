#include "./component.hpp"
ComponentPack::ComponentPack(ComponentTypeLocal comp_type, size_t comp_size) {
  comp_size_ = comp_size;
  comp_type_ = comp_type;

  assertm(comp_size > 0, "[ComponentPack{}] Component Size must be greater than zero");

  components_ = calloc(MAX_COMPONENTS, comp_size);
}

ComponentPack::~ComponentPack() {
  free(components_);
}

void ComponentPack::AddData(EntityId entity, void* component) {
  assert(map_entity_index.find(entity) == map_entity_index.end() &&
         "Component added to same entity more than once.");

  // Put new entry at end and update the maps
  size_t newIndex            = components_count_++;
  map_entity_index[entity]   = newIndex;
  map_index_entity[newIndex] = entity;

  CopyComponent(component, GetComponentByIndex(newIndex));
}

void ComponentPack::RemoveData(EntityId entity) {
  assert(map_entity_index.find(entity) != map_entity_index.end() &&
         "Removing non-existent component.");

  // Copy element at end into deleted element's place to maintain density
  size_t index_to_remove = map_entity_index[entity];
  size_t index_last      = components_count_ - 1;
  // components_[index_to_remove] = components_[index_last];
  // memcpy(GetComponentByIndex(index_to_remove)

  CopyComponent(index_last, index_to_remove);

  // Update map to point to moved spot
  EntityId last_element_entity          = map_index_entity[index_last];
  map_entity_index[last_element_entity] = index_to_remove;
  map_index_entity[index_to_remove]     = last_element_entity;

  map_entity_index.erase(entity);
  map_index_entity.erase(index_last);

  --components_count_;
};

void* ComponentPack::GetComponent(EntityId entity) {
  assert(map_entity_index.find(entity) != map_entity_index.end() &&
         "Retrieving non-existent component.");

  return GetComponentByIndex(map_entity_index[entity]);
};

bool ComponentPack::Contains(EntityId entity) const {
  return map_entity_index.find(entity) != map_entity_index.end();
}

void* ComponentPack::GetComponentByIndex(size_t index) {
  return (void*)((char*)components_ + index * comp_size_);
}

void ComponentPack::CopyComponent(void* src, void* dst) {
  memcpy(dst, src, comp_size_);
}

void ComponentPack::CopyComponent(size_t index_src, size_t index_dst) {
  CopyComponent(GetComponentByIndex(index_src), GetComponentByIndex(index_dst));
}

ComponentManager::ComponentManager() {
  LOG_LVL_COMPONENT_INIT("../log/component.log");
  LOG_LVL_COMPONENT_ROUTINE("ComponentManager initialized");
}

ComponentManager::~ComponentManager() {
  for (auto& pair : component_packs_) {
    delete pair.second;
  }
}

ComponentTypeLocal ComponentManager::RegisterComponent(ComponentTypeGlobal comp_type) {
  // auto type = comp_type;

  // lib<comp_type>.so
  std::string path    = comp_type;
  void*       handler = ImportDLL(path.c_str());

  auto          get_comp_info = (GetComponentInfo)dlsym(handler, "get_component_info");
  ComponentInfo comp_info     = get_comp_info();

  if (component_types_.find(comp_type) != component_types_.end()) {
    LOG_LVL_COMPONENT_ROUTINE("component " << comp_type << " is already registered as"
                                           << component_types_[comp_type]);

    return component_types_[comp_type];
  }

  ComponentTypeLocal comp_type_local = next_++;
  component_types_.insert({comp_type, comp_type_local});

  IComponentPack* pack = new ComponentPack{comp_type_local, comp_info.comp_size};

  component_packs_.insert({comp_type, pack});

  // TODO: add try / catch
  LOG_LVL_COMPONENT_ROUTINE("component " << comp_type << " registered as " << comp_type_local);

  return comp_type_local;
}

ComponentTypeLocal ComponentManager::GetComponentType(ComponentTypeGlobal comp_type) {
  // TODO: assert if the component exists

  return component_types_[comp_type];
}

void ComponentManager::AttachComponent(EntityId entity, ComponentTypeGlobal comp_type,
                                       void* component) {
  GetComponentPack(comp_type)->AddData(entity, component);

  // TODO add try / catch
  LOG_LVL_COMPONENT_ROUTINE("component " << comp_type << "(" << component << ")"
                                         << " attached to entity " << entity);
}

// template <typename Component_t>
void ComponentManager::RemoveComponent(ComponentTypeGlobal comp_type, EntityId entity) {
  GetComponentPack(comp_type)->RemoveData(entity);

  // TODO add try / catch
  LOG_LVL_COMPONENT_ROUTINE("component " << comp_type << "removed from entity " << entity);
}

bool ComponentManager::HasComponent(ComponentTypeGlobal comp_type, EntityId entity) {
  IComponentPack* comp_pack = GetComponentPack(comp_type);

  assertm(comp_pack != nullptr, "[HasComponent] unregistered component");

  return comp_pack->Contains(entity);
}

void* ComponentManager::GetComponent(ComponentTypeGlobal comp_type, EntityId entity) {
  return GetComponentPack(comp_type)->GetComponent(entity);
}

bool ComponentManager::Contains(ComponentTypeGlobal comp_type) {
  return component_types_.find(comp_type) != component_types_.end();
}

void ComponentManager::RemoveEntity(EntityId entity) {
  for (auto& pair : component_packs_) {
    const auto pack = pair.second;

    if (pack->Contains(entity))
      pack->RemoveData(entity);
  }

  // TODO add try / catch
  LOG_LVL_COMPONENT_ROUTINE("entity " << entity << " removed from all component packs");
}

IComponentPack* ComponentManager::GetComponentPack(ComponentTypeGlobal comp_type) {
  // TODO: check if the component is registeredd

  return component_packs_[comp_type];
};