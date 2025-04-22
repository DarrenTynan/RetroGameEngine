//
// Created by Darren Tynan on 15/01/2025.
//

#include "MainMenuBar.h"
#include <SDL2/SDL.h>

namespace EDITOR
{

EDITOR::MainMenuBar::MainMenuBar() = default;

void EDITOR::MainMenuBar::Render(std::shared_ptr<Registry>& registry)
{
    auto logger = EDITOR_LOGGER::Logger::GetInstance();
//    auto fileDialogs = EDITOR_FILEDIALOG::FileDialogs::GetInstance();

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New"))
            {
                // TinyFileDialog
//                auto folderPtr = fileDialogs->SelectFolderDialog2( "New Project", SDL_GetBasePath() );
                // /users/darren/desktop
//                logger->AddLog("New project... %s", folderPtr.c_str());
//                std::cout << folderPtr.c_str() << std::endl;

            }
            if (ImGui::MenuItem("Open", "Ctrl+O"))
            {
                logger->AddLog("File open...");
//                fileDialogs->OpenFileDialog();
            }
            if (ImGui::MenuItem("Open Recent")) {}
            if (ImGui::MenuItem("Save", "Ctrl+S")) {}
            if (ImGui::MenuItem("Save As")) {}
            if (ImGui::MenuItem("Quit")) {}
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
            if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "CTRL+X")) {}
            if (ImGui::MenuItem("Copy", "CTRL+C")) {}
            if (ImGui::MenuItem("Paste", "CTRL+V")) {}
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Debug"))
        {
            if (ImGui::MenuItem("Log Entry"))
            {
                // Instantiate instance
//                auto logger = EDITOR_LOGGER::Logger::GetInstance();
//                EDITOR_LOGGER::Logger::TestLog();
            }
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

}

} // end namespace
