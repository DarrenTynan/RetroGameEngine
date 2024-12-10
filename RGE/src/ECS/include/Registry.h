//
// Created by Darren Tynan on 10/12/2024.
//

#ifndef RETROGAMEENGINE_REGISTRY_H
#define RETROGAMEENGINE_REGISTRY_H

/**
 * @brief The registry manages the creation and destruction of entities,
 * add systems, and components.
 */
class Registry {
private:
    int numEntities = 0;

    // Vector of component pools, each pool contains all the data for a certain component type
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

#endif //RETROGAMEENGINE_REGISTRY_H
