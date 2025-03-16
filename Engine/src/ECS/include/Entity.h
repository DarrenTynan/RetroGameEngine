//
// Created by Darren Tynan on 10/12/2024.
//

#ifndef RETROGAMEENGINE_ENTITY_H
#define RETROGAMEENGINE_ENTITY_H

namespace RGE_ECS
{

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
    void AddGroupTag(const std::string &group);
    [[nodiscard]] bool BelongsToGroup(const std::string &group) const;

    // Operator overloading for entity objects
    Entity& operator = (const Entity& other) = default;
    bool operator == (const Entity& other) const { return id == other.id; }
    bool operator != (const Entity& other) const { return id != other.id; }
    bool operator > (const Entity& other) const { return id > other.id; }
    bool operator < (const Entity& other) const { return id < other.id; }

    // Manage entity components
    template <typename TComponent, typename ...TArgs> void AddComponent(TArgs&& ...args);
    template <typename TComponent>
    [[maybe_unused]] void RemoveComponent();
    template <typename TComponent> [[nodiscard]] bool HasComponent() const;
    template <typename TComponent> TComponent& GetComponent() const;

    // Hold a pointer to the entity's owner registry
    class Registry* registry{};

};


} // end namespace
#endif //RETROGAMEENGINE_ENTITY_H
