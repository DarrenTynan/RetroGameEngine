//
// Created by Darren Tynan on 27/12/2022.
//

#include "include/ECS.h"
#include <string>
#include <algorithm>

int IComponent::nextId = 0;


/**
 * @brief Get the entity id
 *
 * @return
 */
int Entity::GetId() const { return id; }

/**
 * @brief Kill off the entity
 *
 */
void Entity::Kill() { registry->KillEntity(*this); }

/**
 * @brief Add a tag to the entity.
 *
 * @param tag
 */
void Entity::AddTag(const std::string &tag) { registry->TagEntity(*this, tag); }

/**
 * @brief Has the entity got a tag?
 *
 * @param tag
 * @return true / false
 */
bool Entity::HasTag(const std::string &tag) const { return registry->EntityHasTag(*this, tag); }





//************************************
std::string Registry::GetTagById(int _id)
{
    auto taggedEntity = tagPerEntity.find(_id);
    auto tag = taggedEntity->second;
    return tag;

//    if (taggedEntity != tagPerEntity.end())
//    {
//        auto tag = taggedEntity->second;
//        entityPerTag.erase(tag);
//        tagPerEntity.erase(taggedEntity);
//    }

    // Traversing an unordered map
//    for (auto x : tagPerEntity)
//        std::cout << x.first << " " << x.second << std::endl;
//
//    return "DEBUG 1";
}
//************************************

/**
 * @brief Update the entities. Either create new ones or kill off old ones.
 */
void Registry::Update()
{
    // Add the entities that are waiting to be created to the active Systems
    for (auto entity: entitiesToBeAdded)
    {
        AddEntityToSystems(entity);
    }
    entitiesToBeAdded.clear();

    // Remove the entities that are waiting to be killed from the active Systems
    for (auto entity: entitiesToBeKilled)
    {
        RemoveEntityFromSystems(entity);
        entityComponentSignatures[entity.GetId()].reset();
        freeIds.push_back(entity.GetId());

        // Remove any traces of that entity from the tag/group maps
        RemoveEntityTag(entity);
        RemoveEntityFromGroup(entity);
    }
    entitiesToBeKilled.clear();
}

/**
 * @brief Tag entity
 *
 * @param entity
 * @param tag
 */
void Registry::TagEntity(Entity entity, const std::string &tag)
{
    entityPerTag.emplace(tag, entity);
    tagPerEntity.emplace(entity.GetId(), tag);

}

/**
 * @brief Remove tag from the entity
 *
 * @param entity
 */
void Registry::RemoveEntityTag(Entity entity)
{
    auto taggedEntity = tagPerEntity.find(entity.GetId());
    if (taggedEntity != tagPerEntity.end())
    {
        auto tag = taggedEntity->second;
        entityPerTag.erase(tag);
        tagPerEntity.erase(taggedEntity);
    }
}

/**
 * @brief Has the given entity the given tag?
 *
 * @param entity
 * @param tag
 * @return
 */
bool Registry::EntityHasTag(Entity entity, const std::string &tag) const
{
    if (tagPerEntity.find(entity.GetId()) == tagPerEntity.end())
    {
        return false;
    }
    return entityPerTag.find(tag)->second == entity;
}

/**
 * @brief return the entity of the given tag
 *
 * @param tag
 * @return
 */
Entity Registry::GetEntityByTag(const std::string &tag) const { return entityPerTag.at(tag); }


/**
 * @brief Add the entity to a group
 *
 * @param group
 */
void Entity::AddGroupTag(const std::string &group) { registry->GroupTheEntity(*this, group); }

/**
 * @brief Does the entity belong to a group?
 *
 * @param group
 * @return
 */
bool Entity::BelongsToGroup(const std::string &group) const { return registry->EntityBelongsToGroup(*this, group); }

/**
 * @brief Group the entity
 * @param entity
 * @param group
 */
void Registry::GroupTheEntity(Entity entity, const std::string &group)
{
    namePerEntity.emplace(group, std::set < Entity > ());
    namePerEntity[group].emplace(entity);
    groupPerEntity.emplace(entity.GetId(), group);
}

/**
 * @brief Remove given entity from group
 *
 * @param entity
 */
void Registry::RemoveEntityFromGroup(Entity entity)
{
    // if in group, remove entity from group management
    auto groupedEntity = groupPerEntity.find(entity.GetId());
    if (groupedEntity != groupPerEntity.end())
    {
        auto group = namePerEntity.find(groupedEntity->second);
        if (group != namePerEntity.end())
        {
            auto entityInGroup = group->second.find(entity);
            if (entityInGroup != group->second.end())
            {
                group->second.erase(entityInGroup);
            }
        }
        groupPerEntity.erase(groupedEntity);
    }
}

/**
 * @brief Does the given entity belong to a group?
 *
 * @param entity
 * @param group
 * @return
 */
bool Registry::EntityBelongsToGroup(Entity entity, const std::string &group) const
{
//    auto groupEntities = namePerEntity.at(group);
//    return groupEntities.find(entity.GetId()) != groupEntities.end();
    auto groupEntities = namePerEntity.find(group);
    if (groupEntities == namePerEntity.end())
    {
        return false;

    }
    return true;
}

/**
 * @brief Return all entities belonging to given group name
 *
 * @param group
 * @return
 */
std::vector<Entity> Registry::GetEntitiesByGroup(const std::string& group) const
{
    auto& setOfEntities = namePerEntity.at(group);
    return std::vector<Entity>(setOfEntities.begin(), setOfEntities.end());
}


/**
 * @brief Create a new entity object
 *
 * @return new entity
 */
Entity Registry::CreateEntity()
{
    int entityId;

    if (freeIds.empty())
    {
        // If there are no free id's
        entityId = numEntities++;
        if (entityId >= entityComponentSignatures.size())
        {
            entityComponentSignatures.resize(entityId + 1);
        }
    }
    else
    {
        // Reuse an id from the list of previously removed entities
        entityId = freeIds.front();
        freeIds.pop_front();
    }

    Entity entity(entityId);
    entity.registry = this;
    entitiesToBeAdded.insert(entity);

    Logger::Log("Entity created with id = " + std::to_string(entityId));

    return entity;
}

/**
 * @brief Add the given entity to the system
 *
 * @param entity
 */
void Registry::AddEntityToSystems(Entity entity)
{
    const auto entityId = entity.GetId();

    const auto& entityComponentSignature = entityComponentSignatures[entityId];

    for (auto& system: systems)
    {
        const auto& systemComponentSignature = system.second->GetComponentSignature();

        bool isInterested = (entityComponentSignature & systemComponentSignature) == systemComponentSignature;

        if (isInterested) { system.second->AddEntityToSystem(entity); }
    }
}


/**
 * @brief Kill off the given entity
 *
 * @param entity
 */
void Registry::KillEntity(Entity entity) { entitiesToBeKilled.insert(entity); }

/**
 * @brief Remove the given entity from the system
 * @param entity
 */
void Registry::RemoveEntityFromSystems(Entity entity)
{
    for (const auto& system: systems)
    {
        system.second->RemoveEntityFromSystem(entity);
    }
}

/**
 * @brief Add the given entity to the system
 *
 * @param entity
 */
void System::AddEntityToSystem(Entity entity) { entities.push_back(entity); }

/**
 * @brief Remove entity from the system
 *
 * @param entity
 */
void System::RemoveEntityFromSystem(Entity entity)
{
    entities.erase(std::remove_if(entities.begin(), entities.end(), [&entity](Entity other)
    {
        return entity.GetId() == other.GetId();
    }), entities.end());
}

/**
 * @brief Get all the entities on the system
 *
 * @return
 */
std::vector<Entity> System::GetSystemEntities() const { return entities; }

/**
 * @brief Get the component signature
 *
 * @return
 */
const Signature& System::GetComponentSignature() const { return componentSignature; }
