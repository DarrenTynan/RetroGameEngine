//
// Created by Darren Tynan on 11/01/2025.
//

#include "EntityDisplay.h"
#include <SDL2/SDL.h>

#include "../../Engine/src/Components/include/TransformComponent.h"
#include "../../Engine/src/Components/include/RigidbodyComponent.h"
#include "../../Engine/src/Components/include/BoxColliderComponent.h"
#include "../../Engine/src/Components/include/SpriteComponent.h"
#include "include/Logger.h"

using namespace RGE_Component;
using namespace RGE_ECS;
using namespace EDITOR_LOGGER;

namespace EDITOR
{

    EDITOR::EntityDisplay::EntityDisplay() = default;


    void EDITOR::EntityDisplay::Render(std::shared_ptr<Registry>& registry)
    {
        auto player = registry->GetEntityByTag("player");
        auto &transform = player.GetComponent<TransformComponent>();
        auto &rigidbody = player.GetComponent<RigidBodyComponent>();
        auto &boxCollider = player.GetComponent<BoxColliderComponent>();
        auto &sprite = player.GetComponent<SpriteComponent>();

        if (ImGui::Begin("Entity Window"))
        {
            ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
            if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
            {
                if (ImGui::BeginTabItem("Player"))
                {
                    if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_None))
                    {
                        ImGui::Text("Transform Position:");
                        ImGui::SetNextItemWidth(130);
                        ImGui::InputFloat("X", &transform.position.x, 1.00f, 1.0f, "%.2f");

                        ImGui::SameLine(180.0f);
                        ImGui::SetNextItemWidth(130);
                        ImGui::InputFloat("Y", &transform.position.y, 1.00f, 1.0f, "%.2f");

                        ImGui::Separator();
                        ImGui::Text("Transform Scale:");
                        ImGui::SetNextItemWidth(130);
                        ImGui::InputFloat("##X", &transform.scale.x, 0.5f, 1.0f, "%.2f");

                        ImGui::SameLine(180.0f);
                        ImGui::SetNextItemWidth(130);
                        ImGui::InputFloat("##Y", &transform.scale.y, 0.5f, 1.0f, "%.2f");
                    }

                    if (ImGui::CollapsingHeader("Rigidbody", ImGuiTreeNodeFlags_None))
                    {
                        ImGui::Separator();
                        ImGui::Text("Rigidbody DeltaXY:");
                        ImGui::SetNextItemWidth(130);
                        ImGui::InputFloat("##X", &rigidbody.deltaXY.x, 1.0f, 1.0f, "%.2f");

                        ImGui::SameLine(180.0f);
                        ImGui::SetNextItemWidth(130);
                        ImGui::InputFloat("##Y", &rigidbody.deltaXY.y, 1.0f, 1.0f, "%.2f");

                        ImGui::Separator();
                        ImGui::Text("Rigidbody MaxDeltaXY:");
                        ImGui::SetNextItemWidth(130);
                        ImGui::InputFloat("##X", &rigidbody.maxDeltaXY.x, 1.0f, 1.0f, "%.2f");

                        ImGui::SameLine(180.0f);
                        ImGui::SetNextItemWidth(130);
                        ImGui::InputFloat("##Y", &rigidbody.maxDeltaXY.y, 1.0f, 1.0f, "%.2f");

                        ImGui::Separator();
                        ImGui::Text("Rigidbody Acceleration:");
                        ImGui::SetNextItemWidth(130);
                        ImGui::InputFloat("acceleration", &rigidbody.acceleration, 1.0f, 1.0f, "%.2f");

                        ImGui::Separator();
                        ImGui::Text("Rigidbody Boost:");
                        ImGui::SetNextItemWidth(130);
                        ImGui::InputFloat("boost", &rigidbody.boost, 1.0f, 1.0f, "%.2f");

                        ImGui::Separator();
                        ImGui::Text("Rigidbody Gravity:");
                        ImGui::SetNextItemWidth(130);
                        ImGui::InputFloat("gravity", &rigidbody.gravity, 1.0f, 1.0f, "%.2f");

                        ImGui::Separator();
                        ImGui::Text("Rigidbody Friction:");
                        ImGui::SetNextItemWidth(130);
                        ImGui::InputFloat("friction", &rigidbody.friction, 1.0f, 1.0f, "%.2f");
                    }

                    if (ImGui::CollapsingHeader("Box Collider", ImGuiTreeNodeFlags_None))
                    {
                        ImGui::SetNextItemWidth(130);
                        ImGui::InputFloat("w", &boxCollider.width, 0.5f, 1.0f, "%.2f");
                        ImGui::SameLine(180.0f);

                        ImGui::SetNextItemWidth(130);
                        ImGui::InputFloat("h", &boxCollider.height, 0.5f, 1.0f, "%.2f");

                        ImGui::Separator();

                        ImGui::Text("Center:");
                        ImGui::SetNextItemWidth(130);
                        ImGui::InputFloat("x", &boxCollider.center.x, 1.0f, 1.0f, "%.2f");
                        ImGui::SameLine(180.0f);
                        ImGui::SetNextItemWidth(130);
                        ImGui::InputFloat("y", &boxCollider.center.y, 1.0f, 1.0f, "%.2f");
                    }

                    if (ImGui::CollapsingHeader("Sprite", ImGuiTreeNodeFlags_None))
                    {
                        ImGui::Text("ID: %s", sprite.assetId.c_str());
                        ImGui::SetNextItemWidth(130);
                        ImGui::InputInt("w", &sprite.width);
                        ImGui::SameLine(180.0f);
                        ImGui::SetNextItemWidth(130);
                        ImGui::InputInt("h", &sprite.height);
                        ImGui::SetNextItemWidth(130);
                        ImGui::InputInt("z-index", &sprite.zIndex);
                        ImGui::SetNextItemWidth(130);
                        ImGui::Checkbox("IsFixed", &sprite.isFixed);

                        ImGui::Text("Source Rect:");
                        ImGui::SetNextItemWidth(130);
                        float x = sprite.srcRect.x;
                        ImGui::InputFloat("x", &x, 1.00f, 1.0f, "%.2f");

                        ImGui::SameLine(180.0f);
                        ImGui::SetNextItemWidth(130);
                        float y = sprite.srcRect.y;
                        ImGui::InputFloat("y", &y, 1.00f, 1.0f, "%.2f");

                        ImGui::Separator();
                        ImGui::Text("Source Rect:");
                        ImGui::SetNextItemWidth(130);
                        float w = sprite.srcRect.w;
                        ImGui::InputFloat("w", &w, 0.5f, 1.0f, "%.2f");

                        ImGui::SameLine(180.0f);
                        ImGui::SetNextItemWidth(130);
                        float h = sprite.srcRect.h;
                        ImGui::InputFloat("h", &h, 0.5f, 1.0f, "%.2f");

                    }

                    if (ImGui::CollapsingHeader("Animation", ImGuiTreeNodeFlags_None))
                    {}

                    ImGui::EndTabItem();
                }

                if (ImGui::BeginTabItem("Entities"))
                {
                    ImGui::Text("This is the Broccoli tab!\nblah blah blah blah blah");
                    ImGui::EndTabItem();
                }

                if (ImGui::BeginTabItem("Cucumber"))
                {
                    ImGui::Text("This is the Cucumber tab!\nblah blah blah blah blah");
                    ImGui::EndTabItem();
                }
                ImGui::EndTabBar();
            }


        ImGui::End();
}
    }
} // end namespace