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
#include "../../Logger/Logger.h"

#include "Pool.h"
#include "Component.h"

//const unsigned int MAX_COMPONENTS = 32;
//
///**
// * We use a bitset (1s and 0s) to keep track of which components an entity has,
// * and also helps keep track of which entities a system is interested in.
// */
//typedef std::bitset<MAX_COMPONENTS> Signature;
//
//struct IComponent {
//    protected:
//        static int nextId;
//};
//
//
///**
// * @brief Used to assign a unique id to a component type
// *
// * Return the unique id of Component<T>
// *
// * @tparam T
// */
//template <typename T>
//class Component: public IComponent {
//    public:
//        static int GetId() {
//            static auto id = nextId++;
//            return id;
//        }
//};


/**
 * @brief A small class to hold data for entity.
 */
class Entity
{
private:
    int id;
public:
    explicit Entity(int id): id(id) {};
    Entity(const Entity &entity) = default;
    [[nodiscard]] int GetId() const;
    void Kill();

    // Manage entity tags and groups
    void AddTag(const std::string &tag);
    [[nodiscard]] bool HasTag(const std::string &tag) const;
    void Group(const std::string &group);
    [[nodiscard]] bool BelongsToGroup(const std::string &group) const;

    // Operator overloading for entity objects
    Entity& operator = (const Entity& other) = default;
    bool operator == (const Entity& other) const { return id == other.id; }
    bool operator != (const Entity& other) const { return id != other.id; }
    bool operator > (const Entity& other) const { return id > other.id; }
    bool operator < (const Entity& other) const { return id < other.id; }

    // Manage entity components
    template <typename TComponent, typename ...TArgs> void AddComponent(TArgs&& ...args);
    template <typename TComponent> void RemoveComponent();
    template <typename TComponent> [[nodiscard]] bool HasComponent() const;
    template <typename TComponent> TComponent& GetComponent() const;

    // Hold a pointer to the entity's owner registry
    class Registry* registry;

};


/**
 *  @brief The system processes entities that contain a specific signature.
 */
class System {
    private:
        Signature componentSignature;
        std::vector<Entity> entities;

    public:
        System() = default;
        ~System() = default;

        void AddEntityToSystem(Entity entity);
        void RemoveEntityFromSystem(Entity entity);
        [[nodiscard]] std::vector<Entity> GetSystemEntities() const;
        [[nodiscard]] const Signature &GetComponentSignature() const;

        // Defines the component type that entities must have to be considered by the system.
        template <typename TComponent> void RequireComponent();
};


//TODO moved it to a seperate header file Pool.h
///**
// * @brief IPool is just a vector (contiguous data) of objects of type T
// */
//class IPool {
//    public:
//        virtual ~IPool() = default;
//};
//
//
///**
// * @brief A Pool class to hold pointers to entities spawned.
// *
// * @tparam T
// */
//template <typename T>
//class Pool: public IPool {
//    private:
//        std::vector<T> data;
//
//    public:
//        explicit Pool(int size = 100) { data.resize(size); }
//        ~Pool() override = default;
//
//        [[nodiscard]] bool IsEmpty() const { return data.empty(); }
//        [[nodiscard]] int GetSize() const { return data.size(); }
//        void Resize(int n) { data.resize(n); }
//        void Clear() { data.clear(); }
//        void Add(T object) { data.push_back(object); }
//        void Set(int index, T object) { data[index] = object; }
//        T& Get(int index) { return static_cast<T&>(data[index]); }
//        T& operator [](unsigned int index) { return data[index]; }
//};


/**
 * @brief The registry manages the creation and destruction of entities,
 * add systems, and components.
 */
class Registry {
    private:
        int numEntities = 0;

        // Vector of component pools, each pool contains all the data for a certain compoenent type
        // [Vector index = component type id]
        // [Pool index = entity id]
        std::vector<std::shared_ptr<IPool>> componentPools;

        // Vector of component signatures per entity, saying which component is turned "on" for a given entity        std::vector<Signature> entityComponentSignatures;
        // [Vector index = entity id]
        std::vector<Signature> entityComponentSignatures;

        // Map of active systems
        // [Map key = system type id]
        std::unordered_map<std::type_index, std::shared_ptr<System>> systems;

        // Set of entities that are flagged to be added or removed in the next registry UpdateSystems()
        std::set<Entity> entitiesToBeAdded;
        std::set<Entity> entitiesToBeKilled;

        // Entity unique tag
        std::unordered_map<std::string, Entity> entityPerTag;
        std::unordered_map<int, std::string> tagPerEntity;

        // GH
        std::unordered_map<int, std::string> nameOfEntity;

        // Entity group tag
        std::unordered_map<std::string, std::set<Entity>> namePerEntity;
        std::unordered_map<int, std::string> groupPerEntity;

        // List of free entity slot id's that were previously removed after death.
        std::deque<int> freeIds;

    public:
        Registry() { Logger::Log("Registry constructor called"); }

        ~Registry() { Logger::Log("Registry destructor called"); }

        Entity GetEntityById(Entity entity, int _id);

        // The registry UpdateSystems() finally processes the entities that are waiting to be added/killed to the systems
        void Update();

        // Entity management.
        Entity CreateEntity();
        void KillEntity(Entity entity);

        // AddTag management
        void TagEntity(Entity entity, const std::string &tag);
        [[nodiscard]] bool EntityHasTag(Entity entity, const std::string &tag) const;
        [[nodiscard]] Entity GetEntityByTag(const std::string &tag) const;
        void RemoveEntityTag(Entity entity);

        // Group management
        void GroupTheEntity(Entity entity, const std::string &group);
        [[nodiscard]] bool EntityBelongsToGroup(Entity entity, const std::string &group) const;
        [[nodiscard]] std::vector<Entity> GetEntitiesByGroup(const std::string &group) const;
        void RemoveEntityFromGroup(Entity entity);

        // Component management.
        template <typename TComponent, typename ...TArgs> void AddComponent(Entity entity, TArgs&& ...args);
        template <typename TComponent> void RemoveComponent(Entity entity);
        template <typename TComponent> [[nodiscard]] bool HasComponent(Entity entity) const;
        template <typename TComponent> TComponent& GetComponent(Entity entity) const;

        // System management
        template <typename TSystem, typename ...TArgs> void AddSystem(TArgs&& ...args);
        template <typename TSystem> void RemoveSystem();
        template <typename TSystem> [[nodiscard]] bool HasSystem() const;
        template <typename TSystem> TSystem& GetSystem() const;

        // Checks the component signature of an entity and add the entity to the systems
        // that are interested in it
        void AddEntityToSystems(Entity entity);
        void RemoveEntityFromSystems(Entity entity);

};


template <typename TComponent>
void System::RequireComponent() {
    const auto componentId = Component<TComponent>::GetId();
    componentSignature.set(componentId);
}


template <typename TSystem, typename ...TArgs>
void Registry::AddSystem(TArgs&& ...args) {
    std::shared_ptr<TSystem> newSystem = std::make_shared<TSystem>(std::forward<TArgs>(args)...);
    systems.insert(std::make_pair(std::type_index(typeid(TSystem)), newSystem));
}


template <typename TSystem>
void Registry::RemoveSystem() {
    auto system = systems.find(std::type_index(typeid(TSystem)));
    systems.erase(system);
}


template <typename TSystem>
bool Registry::HasSystem() const {
    return systems.find(std::type_index(typeid(TSystem))) != systems.end();
}


template <typename TSystem>
TSystem& Registry::GetSystem() const {
    auto system = systems.find(std::type_index(typeid(TSystem)));
    return *(std::static_pointer_cast<TSystem>(system->second));
}


template <typename TComponent, typename ...TArgs>
void Registry::AddComponent(Entity entity, TArgs&& ...args) {
    const auto componentId = Component<TComponent>::GetId();
    const auto entityId = entity.GetId();

    if (componentId >= componentPools.size()) {
        componentPools.resize(componentId + 1, nullptr);
    }

    if (!componentPools[componentId]) {
        std::shared_ptr<Pool<TComponent>> newComponentPool = std::make_shared<Pool<TComponent>>();
        componentPools[componentId] = newComponentPool;
    }

    std::shared_ptr<Pool<TComponent>> componentPool = std::static_pointer_cast<Pool<TComponent>>(componentPools[componentId]);

    if (entityId >= componentPool->GetSize()) {
        componentPool->Resize(numEntities);
    }

    // Create a new Component object of the type TComponent, and forward the variables to the constructor.
    TComponent newComponent(std::forward<TArgs>(args)...);

    // Add Component to the pool list.
    componentPool->Set(entityId, newComponent);

    // Set the entity component signature.
    entityComponentSignatures[entityId].set(componentId);

    Logger::Log("Component id = " + std::to_string(componentId) + " was added to entity id " + std::to_string(entityId));
}


template <typename TComponent>
void Registry::RemoveComponent(Entity entity) {
    const auto componentId = Component<TComponent>::GetId();
    const auto entityId = entity.GetId();
    entityComponentSignatures[entityId].set(componentId, false);
}


template <typename TComponent>
bool Registry::HasComponent(Entity entity) const {
    const auto componentId = Component<TComponent>::GetId();
    const auto entityId = entity.GetId();
    return entityComponentSignatures[entityId].test(componentId);
}


template <typename TComponent>
TComponent& Registry::GetComponent(Entity entity) const {
    const auto componentId = Component<TComponent>::GetId();
    const auto entityId = entity.GetId();
    auto componentPool = std::static_pointer_cast<Pool<TComponent>>(componentPools[componentId]);
    return componentPool->Get(entityId);
}

template <typename TComponent>
void Entity::RemoveComponent() {
    registry->RemoveComponent<TComponent>(*this);
}


template <typename TComponent>
bool Entity::HasComponent() const {
    return registry->HasComponent<TComponent>(*this);
}

template<typename TComponent, typename ...TArgs>
void Entity::AddComponent(TArgs&& ...args) {
    registry->AddComponent<TComponent>(*this, std::forward<TArgs>(args)...);
}

template <typename TComponent>
TComponent& Entity::GetComponent() const {
    return registry->GetComponent<TComponent>(*this);
}


#endif //RETRO_ENGINE_ECS_H
