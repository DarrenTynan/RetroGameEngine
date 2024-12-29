//
// Created by Darren Tynan on 25/01/2023.
//

#ifndef RETRO_ENGINE_RENDERIMGUISYSTEM_H
#define RETRO_ENGINE_RENDERIMGUISYSTEM_H

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

#include "../ECS/include/ECS.h"

class RenderImGuiSystem: public System
{
    public:
        RenderImGuiSystem() = default;
//        bool show_world_overlay = false;
//        bool show_player_debug = false;
//        bool show_demo_window = false;
//        bool show_spawn_entity = true;
//        bool show_tmx_window = false;
//        bool show_object_window = false;
//        bool show_game_window = false;

    void Update(const std::unique_ptr<Registry>& registry, const SDL_Rect& camera)
    {
        // Start the Dear ImGui frame
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

//        if (show_world_overlay) ShowWorldOverlay(&show_world_overlay, camera);
//        if (show_player_debug) ShowPlayerDebug(registry, camera);
//        if (show_demo_window) ImGui::ShowDemoWindow(&show_demo_window);
//        if (show_spawn_entity) ShowSpawnEntity(registry);
//        if (show_tmx_window) ShowTmxWindow(registry, camera);
//        if (show_object_window) ShowObjectWindow(registry);
//        if (show_game_window) ShowGameGrid();
        ShowWorldWindow(registry, camera);
//        ImGui::ShowDemoWindow();

        // Rendering
        ImGui::Render();

        // Setup Dear ImGui context
        ImGuiIO& io = ImGui::GetIO(); (void)io;
//        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
//        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    }

    void ShowWorldWindow(const std::unique_ptr<Registry> &registry, const SDL_Rect &camera)
    {
        if (ImGui::Begin("World Debug"))
        {
            if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
            {
                if (ImGui::BeginTabItem("Player"))
                {
                    ShowPlayerDebug(registry, camera);
                    ImGui::EndTabItem();
                }

                if (ImGui::BeginTabItem("Objects"))
                {
                    ShowObjectWindow(registry);
                    ImGui::EndTabItem();
                }

                if (ImGui::BeginTabItem("TMX"))
                {
                    ShowTmxWindow(registry, camera);
                    ImGui::EndTabItem();
                }

                if (ImGui::BeginTabItem("Spawn Entity"))
                {
                    ShowSpawnEntity(registry);
                    ImGui::EndTabItem();
                }

                if (ImGui::BeginTabItem("Game Grid"))
                {
                    ShowGameGrid();
                    ImGui::EndTabItem();
                }

                ImGui::EndTabBar();
            }

        }
        ImGui::End();

    }

    void ShowGameGrid()
    {
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
        if (ImGui::Begin("Game Window"))
        {
            int x, y;
            SDL_GetMouseState(&x, &y);
            ImGui::Text("x: %i  y: %i", x, y);
            int tileX = x/32;
            int tileY = y/32;
            ImGui::Text("Tile.x: %i  Tile.y %i", tileX, tileY);
            ImGui::End();
        }

    }

    void ShowObjectWindow(const std::unique_ptr<Registry> &registry)
    {
        if (ImGui::Begin("Game Object"))
        {
            // Left
            static int selected = 0;
            {
                ImGui::BeginChild("left pane", ImVec2(150, 0), ImGuiChildFlags_Borders | ImGuiChildFlags_ResizeX);

                auto entities = System::GetSystemEntities();
                for (auto & entity : entities)
                {
                    Entity a = entity;

                    std::string item_id = "##" + std::to_string(a.GetId());

                    if (ImGui::Selectable(item_id.c_str(), entity.GetId() == selected))
                    {
                        selected = entity.GetId();
                    }
                    ImGui::SameLine();
                    auto tag = registry->GetTagById(a.GetId());
                    ImGui::Text("ID: %02i  Tag: %s", a.GetId(), tag.c_str());
                }
                ImGui::EndChild();
            }
            ImGui::SameLine();

            // Right
            {
                ImGui::BeginGroup();
                ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing())); // Leave room for 1 line below us
                auto tag = registry->GetTagById(selected);
                ImGui::Text("Game Objects:");
                ImGui::Separator();

                ImGui::Text("ID: %02i", selected);
                ImGui::Text("Tag: %s", tag.c_str());

                ImGui::EndChild();
                ImGui::Separator();
                ImGui::EndGroup();
            }
        }

        ImGui::End();

    }

    static void ShowTmxWindow(const std::unique_ptr<Registry> &registry, const SDL_Rect &camera)
    {
        if (ImGui::Begin("TMX Map"))
        {
            int x, y;
            SDL_GetMouseState(&x, &y);
            ImGui::Text("x: %i  y: %i", x, y);
            int tileX = x/32;
            int tileY = y/32;
            ImGui::Text("Tile.x: %i  Tile.y %i", tileX, tileY);

            ImGui::Separator();


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

    static void ShowPlayerDebug(const std::unique_ptr<Registry> &registry, const SDL_Rect &camera)
    {
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
        if (ImGui::Begin("Player Debug"))
        {
            Entity player = registry->GetEntityByTag("player");

            // The fsm ptr is held in RigidBodyComponent.
            auto fsm = player.GetComponent<RigidBodyComponent>().fsm;
            //  The current state is held in fsm
            auto state = fsm->getCurrentState()->getName();

            if (ImGui::CollapsingHeader("Player Entity", ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::Text("Player ID: %i",  player.GetId());

                if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
                {
                    TransformComponent trans = player.GetComponent<TransformComponent>();
                    ImGui::Text("Position: %.2f, %.2f",  trans.position.x, trans.position.y);
                }

                if (ImGui::CollapsingHeader("Rigid Body", ImGuiTreeNodeFlags_DefaultOpen))
                {
                    auto& rb = player.GetComponent<RigidBodyComponent>();
                    auto& tc = player.GetComponent<TransformComponent>();

                    ImGui::Text("Velocity: x: %.2f y: %.2f", rb.velocity.x, rb.velocity.y);
                    ImGui::Text("Old Velocity: x: %.2f y: %.2f", rb.oldVelocity.x, rb.oldVelocity.y);

                    ImGui::Spacing();
                    ImGui::Separator();
                    ImGui::Spacing();

                    static float acceleration = rb.acceleration;
                    ImGui::SetNextItemWidth(150.0);
                    if (ImGui::InputFloat("Acceleration", &acceleration, 1.00f, 1.0f, "%.2f")) { rb.speed = acceleration; }

                    static float maxAcceleration = rb.maxAcceleration;
                    ImGui::SetNextItemWidth(150.0);
                    if (ImGui::InputFloat("Max Acceleration", &maxAcceleration, 1.00f, 1.0f, "%.2f")) { rb.maxAcceleration = maxAcceleration; }

                    static float gravity = rb.gravity;
                    ImGui::SetNextItemWidth(150.0);
                    if (ImGui::InputFloat("Gravity", &gravity, 0.5f, 1.0f, "%.2f")) { rb.gravity = gravity; };

                    static float maxGravity = rb.maxGravity;
                    ImGui::SetNextItemWidth(150.0);
                    if (ImGui::InputFloat("Max Gravity", &maxGravity, 0.5f, 1.0f, "%.2f")) { rb.maxGravity = maxGravity; };

                    static float speed = rb.speed;
                    ImGui::SetNextItemWidth(150.0);
                    if (ImGui::InputFloat("Speed", &speed, 1.00f, 1.0f, "%.2f")) { rb.speed = speed; }

                    ImGui::Separator();

                    static float jumpHeight = rb.jumpHeight;
                    ImGui::SetNextItemWidth(150.0);
                    if (ImGui::InputFloat("Jump Height", &jumpHeight, 0.5f, 1.0f, "%.2f")) { rb.jumpHeight = jumpHeight; };

                    static float jumpFrames = rb.jumpFrames;
                    ImGui::SetNextItemWidth(150.0);
                    if (ImGui::InputFloat("Jump Frames", &jumpFrames, 0.5f, 1.0f, "%.2f")) { rb.jumpFrames = jumpFrames; };

                    static float jumpForce = rb.jumpForce;
                    ImGui::SetNextItemWidth(150.0);
                    if (ImGui::InputFloat("Jump Force", &jumpForce, 0.5f, 1.0f, "%.2f")) { rb.jumpForce = jumpForce; };

                    ImGui::Separator();

                    static float friction = rb.friction;
                    ImGui::SetNextItemWidth(150.0);
                    if (ImGui::InputFloat("Friction", &friction, 0.5f, 1.0f, "%.2f")) { rb.friction = friction;}

                }

                if (ImGui::CollapsingHeader("Finate State Machine", ImGuiTreeNodeFlags_DefaultOpen))
                {
                    ImGui::Text("Current State: %s",  state.c_str());
                    ImGui::Text("isGrounded: %i",  fsm->isGrounded);
                    ImGui::Text("Direction: x: %.2f y: %.2f", fsm->direction.x, fsm->direction.y);
                }

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
