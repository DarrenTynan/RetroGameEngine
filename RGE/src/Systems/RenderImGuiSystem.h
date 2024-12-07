//
// Created by Darren Tynan on 25/01/2023.
//

#ifndef RETRO_ENGINE_RENDERIMGUISYSTEM_H
#define RETRO_ENGINE_RENDERIMGUISYSTEM_H

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>
#include "../ECS/ECS.h"

class RenderImGuiSystem: public System
{
    public:
        RenderImGuiSystem() = default;
        bool show_world_overlay = true;
        bool show_game_debug = true;
        bool show_demo_window = true;
        bool show_spawn_entity = true;
        bool show_tmx_window = true;
        bool show_object_window = true;

    void Update(const std::unique_ptr<Registry>& registry, const SDL_Rect& camera)
    {
        // Start the Dear ImGui frame
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        if (show_world_overlay) ShowWorldOverlay(&show_world_overlay, camera);
        if (show_game_debug) ShowGameDebug(registry, camera);
        if (show_demo_window) ImGui::ShowDemoWindow(&show_demo_window);
        if (show_spawn_entity) ShowSpawnEntity(registry);
        if (show_tmx_window) ShowTmxWindow(registry, camera);
        if (show_object_window) ShowObjectWindow(registry);

        // Rendering
        ImGui::Render();

        // Setup Dear ImGui context
        ImGuiIO& io = ImGui::GetIO(); (void)io;
//        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
//        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    }

//    int i = 0;
//    for (std::vector<std::string>::iterator it = m_items.begin(); it != m_items.end(); ++it)
//    {
//        std::string itemid = "##" + std::to_string(i);
//        if (ImGui::Selectable(itemid.c_str(), i == m_selectedItem))
//        {
//            m_selectedItem = i;
//        }
//        ImGui::SameLine();
//        ImGui::Text("Item: ");
//        ImGui::SameLine();
//        ImGui::Text((*it).c_str());
//        i++;
//    }
    void ShowObjectWindow(const std::unique_ptr<Registry> &registry)
    {
        if (ImGui::Begin("Game Object"))
        {
            // Left
            static int selected = 0;
            {
                ImGui::BeginChild("left pane", ImVec2(150, 0), ImGuiChildFlags_Borders | ImGuiChildFlags_ResizeX);

                auto entities = System::GetSystemEntities();
                for (auto i = entities.begin(); i != entities.end(); i++)
                {
                    Entity a = *i;
                    char label[128];
//                    std::cout << a.GetComponent<BoxColliderComponent>().name << std::endl;
                    std::string item_id = "##" + std::to_string(a.GetId());
                    if (ImGui::Selectable(item_id.c_str(), i->GetId() == selected))
                    {
                        selected = i->GetId();
                    }
                    ImGui::SameLine();
                    ImGui::Text("Object: %i", a.GetId());
                }
                ImGui::EndChild();
            }
            ImGui::SameLine();

            // Right
            {
                ImGui::BeginGroup();
                ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing())); // Leave room for 1 line below us
                ImGui::Text("MyObject: %d", selected);
                ImGui::Separator();
                if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
                {
                    if (ImGui::BeginTabItem("Description"))
                    {
                        ImGui::TextWrapped("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. ");
                        ImGui::EndTabItem();
                    }
                    if (ImGui::BeginTabItem("Details"))
                    {
                        ImGui::Text("ID: 0123456789");
                        ImGui::EndTabItem();
                    }
                    ImGui::EndTabBar();
                }
                ImGui::EndChild();
                if (ImGui::Button("Revert")) {}
                ImGui::SameLine();
                if (ImGui::Button("Save")) {}
                ImGui::EndGroup();
            }
        }

        ImGui::End();

    }


    void ShowTmxWindow(const std::unique_ptr<Registry> &registry, const SDL_Rect &camera)
    {
        if (ImGui::Begin("TMX Map"))
        {
            Entity tile = registry->GetEntityByTag("tile");
            ImGui::Text("Tile ID: %i",  tile.GetId());
            TransformComponent trans = tile.GetComponent<TransformComponent>();
            SpriteComponent sprite = tile.GetComponent<SpriteComponent>();

            ImGui::Text("ID: %s", sprite.assetId.c_str());
            ImGui::Text("Position X: %i",  (int) trans.position.x);
            ImGui::Text("Position Y: %i",  (int) trans.position.y);

            ImGui::Text("Width: %i",  sprite.width);
            ImGui::Text("Height: %i", sprite.height);
            ImGui::Text("FlipH: %i", sprite.flipH);
            ImGui::Text("isFixed: %i", sprite.isFixed);
            ImGui::Text("zIndex: %i", sprite.zIndex);
            ImGui::Text("srcRect x, y: %d, %d", sprite.srcRect.x, sprite.srcRect.y );
        }
        ImGui::End();

    }

    void ShowGameDebug(const std::unique_ptr<Registry> &registry, const SDL_Rect &camera)
    {
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
        if (ImGui::Begin("Game Debug"))
        {
            Entity player = registry->GetEntityByTag("player");

            if (ImGui::CollapsingHeader("Player Entity"))
            {
                ImGui::Text("Player ID: %i",  player.GetId());
//                ImGui::Text("Player Name: %s",  player.name_ptr);

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


    void ShowSpawnEntity(const std::unique_ptr<Registry>& registry)
    {
        if (ImGui::Begin("Spawn Entity"))
        {
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
    void ShowWorldOverlay(bool* p_open, const SDL_Rect& camera)
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
                if (ImGui::MenuItem("Custom",       nullptr, location == -1)) location = -1;
                if (ImGui::MenuItem("Center",       nullptr, location == -2)) location = -2;
                if (ImGui::MenuItem("Top-left",     nullptr, location == 0)) location = 0;
                if (ImGui::MenuItem("Top-right",    nullptr, location == 1)) location = 1;
                if (ImGui::MenuItem("Bottom-left",  nullptr, location == 2)) location = 2;
                if (ImGui::MenuItem("Bottom-right", nullptr, location == 3)) location = 3;
                if (p_open && ImGui::MenuItem("Close")) *p_open = false;
                ImGui::EndPopup();
            }
        }
        ImGui::End();
    }

};
#endif //RETRO_ENGINE_RENDERIMGUISYSTEM_H
