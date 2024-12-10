//
// Created by Darren Tynan on 27/12/2022.
//

#include "include/ECS.h"
#include <string>
#include <algorithm>

int IComponent::nextId = 0;

int Entity::GetId() const {
    return id;
}

void Entity::Kill() {
    registry->KillEntity(*this);
}

void Entity::AddTag(const std::string &tag) {
    registry->TagEntity(*this, tag);
}

bool Entity::HasTag(const std::string &tag) const {
    return registry->EntityHasTag(*this, tag);
}

void Entity::Group(const std::string &group) {
    registry->GroupTheEntity(*this, group);
}

bool Entity::BelongsToGroup(const std::string &group) const {
    return registry->EntityBelongsToGroup(*this, group);
}

void Registry::TagEntity(Entity entity, const std::string &tag) {
    entityPerTag.emplace(tag, entity);
    tagPerEntity.emplace(entity.GetId(), tag);

    // GH
    nameOfEntity.emplace(entity.GetId(), tag);

}
// GH
//Entity Registry::GetTagByEntity(const int _id) const {
//    return namePerEntity.key_eq(_id);
//}


void Registry::RemoveEntityTag(Entity entity) {
    auto taggedEntity = tagPerEntity.find(entity.GetId());
    if (taggedEntity != tagPerEntity.end()) {
        auto tag = taggedEntity->second;
        entityPerTag.erase(tag);
        tagPerEntity.erase(taggedEntity);
    }
}

bool Registry::EntityHasTag(Entity entity, const std::string &tag) const {
    if (tagPerEntity.find(entity.GetId()) == tagPerEntity.end()) {
        return false;
    }
    return entityPerTag.find(tag)->second == entity;
}

Entity Registry::GetEntityByTag(const std::string &tag) const {
    return entityPerTag.at(tag);
}


void Registry::GroupTheEntity(Entity entity, const std::string &group) {
    namePerEntity.emplace(group, std::set < Entity > ());
    namePerEntity[group].emplace(entity);
    groupPerEntity.emplace(entity.GetId(), group);
}

void Registry::RemoveEntityFromGroup(Entity entity) {
    // if in group, remove entity from group management
    auto groupedEntity = groupPerEntity.find(entity.GetId());
    if (groupedEntity != groupPerEntity.end()) {
        auto group = namePerEntity.find(groupedEntity->second);
        if (group != namePerEntity.end()) {
            auto entityInGroup = group->second.find(entity);
            if (entityInGroup != group->second.end()) {
                group->second.erase(entityInGroup);
            }
        }
        groupPerEntity.erase(groupedEntity);
    }
}

bool Registry::EntityBelongsToGroup(Entity entity, const std::string &group) const {
//    auto groupEntities = namePerEntity.at(group);
//    return groupEntities.find(entity.GetId()) != groupEntities.end();
    auto groupEntities = namePerEntity.find(group);
    if (groupEntities == namePerEntity.end())
    {
        return false;

    }
    return true;}

std::vector<Entity> Registry::GetEntitiesByGroup(const std::string& group) const {
    auto& setOfEntities = namePerEntity.at(group);
    return std::vector<Entity>(setOfEntities.begin(), setOfEntities.end());
}


Entity Registry::CreateEntity()
{
    int entityId;


    if (freeIds.empty()) {
        // If there are no free id's
        entityId = numEntities++;
        if (entityId >= entityComponentSignatures.size()) {
            entityComponentSignatures.resize(entityId + 1);
        }
    }
    else {
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
        RemoveEntityFromGroup(entity);
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
