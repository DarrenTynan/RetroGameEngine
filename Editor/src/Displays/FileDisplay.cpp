//
// Created by Darren Tynan on 24/01/2025.
//

#include "FileDisplay.h"

EDITOR::FileDisplay::FileDisplay() {}

void EDITOR::FileDisplay::Render()
{
    if ( ImGui::Begin( "File System" ) )
    {
        if ( ImGui::Button( "Button 1" ) )
        {
            auto fileDialog = EDITOR_FILEDIALOG::FileDialogs::GetInstance();
            fileDialog->GetFolderTree();
            ImGui::Text("Button 1");
        }

    }
    ImGui::End();

}
