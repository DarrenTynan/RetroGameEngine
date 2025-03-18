#ifndef SCRIPTSYSTEM_H
#define SCRIPTSYSTEM_H

//#include "ECS/include/ECS.h"
#include "/Users/darren/Development/C++_Projects/RetroGameEngine/Engine/src/ECS/include/ECS.h"
#include "/Users/darren/Development/C++_Projects/RetroGameEngine/Engine/src/Components/include/TransformComponent.h"
#include "/Users/darren/Development/C++_Projects/RetroGameEngine/Engine/src/Components/include/RigidBodyComponent.h"
#include "/Users/darren/Development/C++_Projects/RetroGameEngine/Engine/src/Components/include/AnimationComponent.h"
#include "/Users/darren/Development/C++_Projects/RetroGameEngine/Engine/src/Components/include/ProjectileEmitterComponent.h"
#include "/Users/darren/Development/C++_Projects/RetroGameEngine/Engine/src/Components/include/ScriptComponent.h"
#include <tuple>

using namespace RGE_ECS;
using namespace RGE_Component;

namespace RGE_System
{

std::tuple<double, double> GetEntityPosition(Entity entity)
{
    if (entity.HasComponent<TransformComponent>())
    {
        const auto transform = entity.GetComponent<TransformComponent>();
        return std::make_tuple(transform.position.x, transform.position.y);
    }
    else
    {
//        Logger::Error("Trying to get the position of an entity that has no transform component");
        return std::make_tuple(0.0, 0.0);
    }
}

std::tuple<double, double> GetEntityVelocity(Entity entity)
{
    if (entity.HasComponent<RigidBodyComponent>())
    {
        const auto rigidbody = entity.GetComponent<RigidBodyComponent>();
        return std::make_tuple(rigidbody.velocityDelta.x, rigidbody.velocityDelta.y);
    }
    else
    {
//        Logger::Error("Trying to get the velocityDelta of an entity that has no rigidbody component");
        return std::make_tuple(0.0, 0.0);
    }
}

void SetEntityPosition(Entity entity, double x, double y)
{
    if (entity.HasComponent<TransformComponent>())
    {
        auto& transform = entity.GetComponent<TransformComponent>();
        transform.position.x = x;
        transform.position.y = y;
    }
    else
    {
//        Logger::Error("Trying to set the position of an entity that has no transform component");
    }
}

void SetEntityVelocity(Entity entity, double x, double y)
{
    if (entity.HasComponent<RigidBodyComponent>())
    {
        auto& rigidbody = entity.GetComponent<RigidBodyComponent>();
        rigidbody.velocityDelta.x = x;
        rigidbody.velocityDelta.y = y;
    }
    else
    {
//        Logger::Error("Trying to set the velocityDelta of an entity that has no rigidbody component");
    }
}

void SetEntityRotation(Entity entity, double angle)
{
    if (entity.HasComponent<TransformComponent>())
    {
        auto& transform = entity.GetComponent<TransformComponent>();
        transform.rotation = angle;
    }
    else
    {
//        Logger::Error("Trying to set the rotation of an entity that has no transform component");
    }
}

void SetEntityAnimationFrame(Entity entity, int frame)
{
    if (entity.HasComponent<AnimationComponent>()) {
        auto& animation = entity.GetComponent<AnimationComponent>();
        animation.currentFrame = frame;
    }
    else
    {
//        Logger::Error("Trying to set the animation frame of an entity that has no animation component");
    }
}

void SetProjectileVelocity(Entity entity, double x, double y)
{
    if (entity.HasComponent<ProjectileEmitterComponent>()) {
        auto& projectileEmitter = entity.GetComponent<ProjectileEmitterComponent>();
        projectileEmitter.projectileVelocity.x = x;
        projectileEmitter.projectileVelocity.y = y;
    }
    else
    {
//        Logger::Error("Trying to set the projectile velocityDelta of an entity that has no projectile emitter component");
    }
}

class ScriptSystem: public System
{
    public:
        ScriptSystem()
        {
            RequireComponent<ScriptComponent>();
        }

        static void CreateLuaBindings(sol::state& lua)
        {
            // Create the "entity" usertype so Lua knows what an entity is
            lua.new_usertype<Entity>(
                "entity",
                "get_id", &Entity::GetId,
                "Destroy", &Entity::Kill,
                "has_tag", &Entity::HasTag,
                "belongs_to_group", &Entity::BelongsToGroup
            );

            // Create all the bindings between C++ and Lua functions
            lua.set_function("get_position", GetEntityPosition);
            lua.set_function("get_velocity", GetEntityVelocity);
            lua.set_function("set_position", SetEntityPosition);
            lua.set_function("set_velocity", SetEntityVelocity);
            lua.set_function("set_rotation", SetEntityRotation);
            lua.set_function("set_projectile_velocity", SetProjectileVelocity);
            lua.set_function("set_animation_frame", SetEntityAnimationFrame);
        }

        void Update(double deltaTime, int elapsedTime)
        {
            // Loop all entities that have a script component and invoke their Lua function
            for (auto entity: GetSystemEntities())
            {
                const auto script = entity.GetComponent<ScriptComponent>();
                script.func(entity, deltaTime, elapsedTime);
                // here is where we invoke a sol::function
            }
        }
};

} // end namespace
#endif
