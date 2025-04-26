//
// Created by Darren Tynan on 11/01/2025.
//

#include "ProjectMenuDisplay.h"
#include "../FileSystem/include/FileHandler.h"

namespace EDITOR_DISPLAY
{

    ProjectMenuDisplay::ProjectMenuDisplay()
    {
        auto fh = EDITOR_FILEHANDLER::FileHandler::GetInstance();
        fh->LoadConfigFile();
//    this->project_name = fh->doc["configuration"]["project_name"].GetString();
//    this->file_path = fh->doc["configuration"]["file_path"].GetString();
//    this->window_width = fh->doc["configuration"]["window_width"].GetInt();
//    this->window_height = fh->doc["configuration"]["window_height"].GetInt();
//    this->window_title = fh->doc["configuration"]["window_title"].GetString();
    }

    void ProjectMenuDisplay::Render(std::shared_ptr<Registry>& registry)
    {
        if (ImGui::Begin("Retro Game_Engine Engine"))
        {
            if (ImGui::Button("Create"))
            {
                ImGui::Text("Create Project");
            }

            ImGui::SameLine();

            if (ImGui::Button("Import"))
            {
                ImGui::Text("Import Project");
            }

            ImGui::SameLine();

            if (ImGui::Button("Edit"))
            {
                ImGui::Text("Edit Project");
            }

            ImGui::SameLine();

            if (ImGui::Button("Run"))
            {
                ImGui::Text("Run Project");
            }

            ImGui::Separator();

            ImGui::Text("Project Name: %s", project_name.c_str());
            ImGui::Text("Project Folder: %s", file_path.c_str());

            ImGui::Separator();

        }
        ImGui::End();

    }
} // end namespace