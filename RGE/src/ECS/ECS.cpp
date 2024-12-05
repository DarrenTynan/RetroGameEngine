//
// Created by Darren Tynan on 27/12/2022.
//

#include "ECS.h"
#include <string>
#include <algorithm>

int IComponent::nextId = 0;

/**
 * @brief Brief description of this function
 *
 * @return int ID
 */
int Entity::GetId() const {
    return id;
}

/**
 * @brief Kill the entity.
 */
void Entity::Kill() {
    registry->KillEntity(*this);
}

/**
 * @brief Adds a tag name to the entity.
 *
 * @param tag: the tag name to use.
 */
void Entity::SetTag(const std::string &tag)
{
    registry->TagEntity(*this, tag);
}

/**
 * @brief SetTag overload
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
 * @brief Returns whether and entity has the given tag.
 *
 * @param tag
 * @return true / false
 */
bool Entity::HasTag(const std::string &tag) const
{
    return registry->EntityHasTag(*this, tag);
}

/**
 * @brief Remove entity by tag name.
 *
 * @param entity
 */
void Registry::RemoveEntityTag(Entity entity)
{
    auto taggedEntity = tagPerEntity.find(entity.GetId());
    if (taggedEntity != tagPerEntity.end()) {
        auto tag = taggedEntity->second;
        entityPerTag.erase(tag);
        tagPerEntity.erase(taggedEntity);
    }
}

/**
 * @brief Has the given entity got an assigned tag name?
 *
 * @param entity
 * @param tag
 * @return true / false
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
 * @brief Set the group name of the entity.
 *
 * @param group name
 */
void Entity::SetGroup(const std::string &group)
{
    registry->GroupEntity(*this, group);
}

/**
 * @brief Does the entity belong to the given group.
 * @param group
 * @return
 */
bool Entity::BelongsToGroup(const std::string &group) const {
    return registry->EntityBelongsToGroup(*this, group);
}





const std::string& Entity::getEntityTageName() const
{
    return entityTageName;
}

//void Entity::SetTag(const std::string &tag)
//{
//    registry->TagEntity(*this, tag);
//}

void Entity::setEntityTageName(const std::string& _entityTageName)
{
    entityTageName = _entityTageName;
}





/**
 * @brief Group the entity in given group name.
 *
 * @param entity
 * @param group
 */
void Registry::GroupEntity(Entity entity, const std::string &group) {
    entitiesPerGroup.emplace(group, std::set<Entity>());
    entitiesPerGroup[group].emplace(entity);
    groupPerEntity.emplace(entity.GetId(), group);
}

/**
 * @brief Remove the entity from given group name.
 * @param entity
 */
void Registry::RemoveEntityGroup(Entity entity) {
    // if in group, remove entity from group management
    auto groupedEntity = groupPerEntity.find(entity.GetId());
    if (groupedEntity != groupPerEntity.end()) {
        auto group = entitiesPerGroup.find(groupedEntity->second);
        if (group != entitiesPerGroup.end()) {
            auto entityInGroup = group->second.find(entity);
            if (entityInGroup != group->second.end()) {
                group->second.erase(entityInGroup);
            }
        }
        groupPerEntity.erase(groupedEntity);
    }
}

/**
 * @brief Get the entity by given tag.
 *
 * @param tag
 * @return
 */
Entity Registry::GetEntityByTag(const std::string &tag) const {
    return entityPerTag.at(tag);
}


/**
 * @brief Does the entity belong in the given group name.
 *
 * @param entity
 * @param group
 * @return
 */
bool Registry::EntityBelongsToGroup(Entity entity, const std::string &group) const {
//    auto groupEntities = entitiesPerGroup.at(group);
//    return groupEntities.find(entity.GetId()) != groupEntities.end();
    auto groupEntities = entitiesPerGroup.find(group);
    if (groupEntities == entitiesPerGroup.end())
    {
        return false;

    }
    return true;
}

/**
 * @brief Return a array of entities in given group name.
 *
 * @param group
 * @return array of entities.
 */
std::vector<Entity> Registry::GetEntitiesByGroup(const std::string& group) const {
    auto& setOfEntities = entitiesPerGroup.at(group);
    return std::vector<Entity>(setOfEntities.begin(), setOfEntities.end());
}


/**
 * @brief Create an entity abd assing an ID.
 *
 * @return entity
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

void Registry::AddEntityToSystems(Entity entity) {
    const auto entityId = entity.GetId();

    const auto& entityComponentSignature = entityComponentSignatures[entityId];

    for (auto& system: systems) {
        const auto& systemComponentSignature = system.second->GetComponentSignature();

        bool isInterested = (entityComponentSignature & systemComponentSignature) == systemComponentSignature;

        if (isInterested) {
            system.second->AddEntityToSystem(entity);
        }
    }
}

void Registry::Update() {
    // Add the entities that are waiting to be created to the active Systems
    for (auto entity: entitiesToBeAdded) {
        AddEntityToSystems(entity);
    }
    entitiesToBeAdded.clear();

    // Remove the entities that are waiting to be killed from the active Systems
    for (auto entity: entitiesToBeKilled) {
        RemoveEntityFromSystems(entity);
        entityComponentSignatures[entity.GetId()].reset();
        freeIds.push_back(entity.GetId());

        // Remove any traces of that entity from the tag/group maps
        RemoveEntityTag(entity);
        RemoveEntityGroup(entity);
    }
    entitiesToBeKilled.clear();
}

void Registry::KillEntity(Entity entity) {
    entitiesToBeKilled.insert(entity);
}

void Registry::RemoveEntityFromSystems(Entity entity) {
    for (const auto& system: systems) {
        system.second->RemoveEntityFromSystem(entity);
    }
}

void System::AddEntityToSystem(Entity entity) {
    entities.push_back(entity);
}

void System::RemoveEntityFromSystem(Entity entity) {
    entities.erase(std::remove_if(entities.begin(), entities.end(), [&entity](Entity other) {
        return entity.GetId() == other.GetId();
    }), entities.end());
}

std::vector<Entity> System::GetSystemEntities() const {
    return entities;
}

const Signature& System::GetComponentSignature() const {
    return componentSignature;
}
