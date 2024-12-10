//
// Created by Darren Tynan on 10/12/2024.
//

#ifndef RETROGAMEENGINE_ENTITY_H
#define RETROGAMEENGINE_ENTITY_H

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

#endif //RETROGAMEENGINE_ENTITY_H
