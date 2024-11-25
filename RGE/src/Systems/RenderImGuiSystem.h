//
// Created by Darren Tynan on 25/01/2023.
//

#ifndef RETRO_ENGINE_RENDERIMGUISYSTEM_H
#define RETRO_ENGINE_RENDERIMGUISYSTEM_H

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

#include "../ECS/ECS.h"

class RenderImGuiSystem: public System {
    public:
        RenderImGuiSystem() = default;
        bool show_world_overlay = true;
        bool show_game_debug = true;
        bool show_demo_window = false;
        bool show_spawn_entity = false;

    void Update(const std::unique_ptr<Registry>& registry, const SDL_Rect& camera) {
        // Start the Dear ImGui frame
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        if (show_world_overlay) ShowWorldOverlay(&show_world_overlay, camera);
        if (show_game_debug) ShowGameDebug(registry, camera);
        if (show_demo_window) ImGui::ShowDemoWindow(&show_demo_window);
        if (show_spawn_entity) ShowSpawnEntity(registry);

        // Rendering
        ImGui::Render();
//        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());

    }

    static void ShowGameDebug(const std::unique_ptr<Registry> &registry, const SDL_Rect &camera) {
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
        if (ImGui::Begin("Game Debug")) {
            Entity player = registry->GetEntityByTag("player");
            if (ImGui::CollapsingHeader("Player Entity"))
            {
                ImGui::Text("Player ID: %i",  player.GetId());

                if (ImGui::CollapsingHeader("Transform"))
                {
                    TransformComponent trans = player.GetComponent<TransformComponent>();
                    ImGui::Text("Position: %.2f, %.2f",  trans.position.x, trans.position.y);
                }

                ImGui::Spacing();

                if (ImGui::CollapsingHeader("Rigid Body"))
                {
                    RigidBodyComponent rb = player.GetComponent<RigidBodyComponent>();
                    ImGui::Text("Direction: %.2f %.2f", rb.direction.x, rb.direction.y);
                    ImGui::Text("Delta: %.2f %.2f", rb.delta.x, rb.delta.y);
                    ImGui::Text("Speed: %.2f", rb.speed);
                    ImGui::Text("Gravity: %.2f", rb.gravity);
                }

                ImGui::Spacing();

                if (ImGui::CollapsingHeader("Ray cast"))
                {
                    RaycastComponent rc = player.GetComponent<RaycastComponent>();
                    ImGui::Text("Ray Start: %.2f %.2f", rc.rayStart.x, rc.rayStart.y);
                    ImGui::Text("Ray End: %.2f %.2f", rc.rayEnd.x, rc.rayEnd.y);
                    ImGui::Text("Map Size: %.1f %.1f", rc.mapSize.x, rc.mapSize.y);
                    ImGui::Text("Cell Size: %.1f %.1f", rc.cellSize.x, rc.cellSize.y);
                    ImGui::Text("Ray Direction: %.1f %.1f", rc.rayDirection.x, rc.rayDirection.y);
                    ImGui::Text("Mouse Position: %.2f %.2f", rc.mousePosition.x, rc.mousePosition.y);
                    ImGui::Text("Ray Unit Step Size: %.2f %.2f", rc.rayUnitStepSize.x, rc.rayUnitStepSize.y);
                }
            }
        }
        ImGui::End();

    }

    static void ShowSpawnEntity(const std::unique_ptr<Registry>& registry)
    {
        if (ImGui::Begin("Spawn Entity")) {
            static int entityXpos = 0;
            static int entityYpos = 0;
            static int scaleX = 1;
            static int scaleY = 1;
            static int rotation = 0;
            static int velocityX = 20;
            static int velocityY = 0;
            ImGui::InputInt("X position", &entityXpos);
            ImGui::InputInt("Y position", &entityYpos);
            ImGui::InputInt("X scale", &scaleX);
            ImGui::InputInt("Y scale", &scaleY);
            ImGui::InputInt("Rotation", &rotation);
            ImGui::InputInt("X velocity", &velocityX);
            ImGui::InputInt("Y scale", &velocityY);

            // Create button
            if (ImGui::Button("Create"))
            {
                Entity chopper = registry->CreateEntity();
                chopper.AddComponent<TransformComponent>(glm::vec2(entityXpos, entityYpos), glm::vec2(scaleX, scaleY), rotation);
                chopper.AddComponent<RigidBodyComponent>(glm::vec2(velocityX, velocityY));
                chopper.AddComponent<SpriteComponent>("chopper-image", 32, 32, 1, false);
                chopper.AddComponent<AnimationComponent>(2, 8, true);
            }
        }
        ImGui::End();

    }

    // Demonstrate creating a simple static window with no decoration
    // + a context-menu to choose which corner of the screen to use.
    static void ShowWorldOverlay(bool* p_open, const SDL_Rect& camera)
    {
        static int location = 0;
        ImGuiIO& io = ImGui::GetIO();
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
        if (location >= 0)
        {
            const float PAD = 10.0f;
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImVec2 work_pos = viewport->WorkPos; // Use work area to avoid menu-bar/task-bar, if any!
            ImVec2 work_size = viewport->WorkSize;
            ImVec2 window_pos, window_pos_pivot;
            window_pos.x = (location & 1) ? (work_pos.x + work_size.x - PAD) : (work_pos.x + PAD);
            window_pos.y = (location & 2) ? (work_pos.y + work_size.y - PAD) : (work_pos.y + PAD);
            window_pos_pivot.x = (location & 1) ? 1.0f : 0.0f;
            window_pos_pivot.y = (location & 2) ? 1.0f : 0.0f;
            ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
            window_flags |= ImGuiWindowFlags_NoMove;
        }
        else if (location == -2)
        {
            // Center window
            ImGui::SetNextWindowPos(ImGui::GetMainViewport()->GetCenter(), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
            window_flags |= ImGuiWindowFlags_NoMove;
        }
        ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
        if (ImGui::Begin("World Info", p_open, window_flags))
        {
//            IMGUI_DEMO_MARKER("Examples/Simple Overlay");
            ImGui::Text("right-click to change position");
            ImGui::Separator();
            if (ImGui::IsMousePosValid())
                ImGui::Text("Mouse Position: (%.1f,%.1f)", io.MousePos.x, io.MousePos.y);
            else
                ImGui::Text("Mouse Position: <invalid>");

            ImGui::Text("Camera X / Y: (%.1i, %.1i)", camera.x, camera.y);
            ImGui::Text("Camera W / H: (%.1i, %.1i)", camera.w, camera.h);

            if (ImGui::BeginPopupContextWindow())
            {
                if (ImGui::MenuItem("Custom",       NULL, location == -1)) location = -1;
                if (ImGui::MenuItem("Center",       NULL, location == -2)) location = -2;
                if (ImGui::MenuItem("Top-left",     NULL, location == 0)) location = 0;
                if (ImGui::MenuItem("Top-right",    NULL, location == 1)) location = 1;
                if (ImGui::MenuItem("Bottom-left",  NULL, location == 2)) location = 2;
                if (ImGui::MenuItem("Bottom-right", NULL, location == 3)) location = 3;
                if (p_open && ImGui::MenuItem("Close")) *p_open = false;
                ImGui::EndPopup();
            }
        }
        ImGui::End();
    }

};
#endif //RETRO_ENGINE_RENDERIMGUISYSTEM_H
