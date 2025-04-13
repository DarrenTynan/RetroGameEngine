//
// Created by Darren Tynan on 27/12/2022.
//

#ifndef RETRO_ENGINE_ECS_H
#define RETRO_ENGINE_ECS_H

#include <string>
#include <bitset>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <set>
#include <memory>
#include <deque>
#include <algorithm>
// Includes MUST be in order. Entity.h, System.h and Registry.h
#include "Pool.h"
#include "Component.h"
#include "Entity.h"
#include "System.h"
#include "Registry.h"

namespace RGE_ECS
{

/**
 * @brief Registry templates
 *
 * @tparam TSystem
 * @tparam TArgs
 * @param args
 */
template <typename TSystem, typename ...TArgs>
void Registry::AddSystem(TArgs&& ...args)
{
    std::shared_ptr<TSystem> newSystem = std::make_shared<TSystem>(std::forward<TArgs>(args)...);
    systems.insert(std::make_pair(std::type_index(typeid(TSystem)), newSystem));
}

/**
 * @brief Remove the system
 *
 * @tparam TSystem
 */
template <typename TSystem>
    [[maybe_unused]] void Registry::RemoveSystem()
{
    auto system = systems.find(std::type_index(typeid(TSystem)));
    systems.erase(system);
}

/**
 * @brief Check for given system
 *
 * @tparam TSystem
 * @return
 */
template <typename TSystem>
    [[maybe_unused]] bool Registry::HasSystem() const {
    return systems.find(std::type_index(typeid(TSystem))) != systems.end();
}

/**
 * @brief Get the given system
 *
 * @tparam TSystem
 * @return
 */
template <typename TSystem>
TSystem& Registry::GetSystem() const
{
    auto system = systems.find(std::type_index(typeid(TSystem)));
    return *(std::static_pointer_cast<TSystem>(system->second));
}

/**
 * @brief Add the given component to the given entity
 *
 * @tparam TComponent
 * @tparam TArgs
 * @param entity
 * @param args
 */
template <typename TComponent, typename ...TArgs>
void Registry::AddComponent(Entity entity, TArgs&& ...args)
{
    const auto componentId = Component<TComponent>::GetId();
    const auto entityId = entity.GetId();

    if (componentId >= componentPools.size())
    {
        componentPools.resize(componentId + 1, nullptr);
    }

    if (!componentPools[componentId])
    {
        std::shared_ptr<Pool<TComponent>> newComponentPool = std::make_shared<Pool<TComponent>>();
        componentPools[componentId] = newComponentPool;
    }

    std::shared_ptr<Pool<TComponent>> componentPool = std::static_pointer_cast<Pool<TComponent>>(componentPools[componentId]);

    if (entityId >= componentPool->GetSize()) { componentPool->Resize(numEntities); }

    // Create a new Component object of the type TComponent, and forward the variables to the constructor.
    TComponent newComponent(std::forward<TArgs>(args)...);

    // Add Component to the pool list.
    componentPool->Set(entityId, newComponent);

    // Set the entity component signature.
    entityComponentSignatures[entityId].set(componentId);

//    Logger::Log("Component id = " + std::to_string(componentId) + " was added to entity id " + std::to_string(entityId));
}

/**
 * @brief Remove component from given entity
 *
 * @tparam TComponent
 * @param entity
 */
template <typename TComponent>
void Registry::RemoveComponent(Entity entity) {
    const auto componentId = Component<TComponent>::GetId();
    const auto entityId = entity.GetId();
    entityComponentSignatures[entityId].set(componentId, false);
}

/**
 * @brief Check if given entity has given component
 *
 * @tparam TComponent
 * @param entity
 * @return
 */
template <typename TComponent>
bool Registry::HasComponent(Entity entity) const {
    const auto componentId = Component<TComponent>::GetId();
    const auto entityId = entity.GetId();
    return entityComponentSignatures[entityId].test(componentId);
}

/**
 * @brief Get component from the given entity
 *
 * @tparam TComponent
 * @param entity
 * @return
 */
template <typename TComponent>
TComponent& Registry::GetComponent(Entity entity) const {
    const auto componentId = Component<TComponent>::GetId();
    const auto entityId = entity.GetId();
    auto componentPool = std::static_pointer_cast<Pool<TComponent>>(componentPools[componentId]);
    return componentPool->Get(entityId);
}


/*
 * @brief Entity template.
 */
template <typename TComponent>
    [[maybe_unused]] void Entity::RemoveComponent() { registry->RemoveComponent<TComponent>(*this); }

/**
 * @brief Has the given entity got a component?
 *
 * @tparam TComponent
 * @return
 */
template <typename TComponent>
bool Entity::HasComponent() const { return registry->HasComponent<TComponent>(*this); }

/**
 * @brief Add the given component the entity
 *
 * @tparam TComponent
 * @tparam TArgs
 * @param args
 */
template<typename TComponent, typename ...TArgs>
void Entity::AddComponent(TArgs&& ...args) {
    registry->AddComponent<TComponent>(*this, std::forward<TArgs>(args)...);
}

/**
 * @brief Get component
 *
 * @tparam TComponent
 * @return
 */
template <typename TComponent>
TComponent& Entity::GetComponent() const {
    return registry->GetComponent<TComponent>(*this);
}


} // end namespace
#endif //RETRO_ENGINE_ECS_H
