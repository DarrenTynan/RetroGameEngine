//
// Created by Darren Tynan on 10/12/2024.
//

#ifndef RETROGAMEENGINE_SYSTEM_H
#define RETROGAMEENGINE_SYSTEM_H

namespace RGE_ECS
{

/**
 *  @brief The system processes entities that contain a specific signature.
 */
class System
{
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

/**
 * @brief A component is mandatory
 *
 * @tparam TComponent
 */
template <typename TComponent>
void System::RequireComponent()
{
    const auto componentId = Component<TComponent>::GetId();
    componentSignature.set(componentId);
}

} // end namespace
#endif //RETROGAMEENGINE_SYSTEM_H
