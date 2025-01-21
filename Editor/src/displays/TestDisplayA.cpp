//
// Created by Darren Tynan on 11/01/2025.
//

#include "TestDisplayA.h"
#include "../libs/nativefiledialog-extended/src/include/nfd.h"

EDITOR::TestDisplayA::TestDisplayA() {}

void EDITOR::TestDisplayA::Render()
{
    if ( ImGui::Begin( "Test Window A" ) )
    {
        if ( ImGui::Button( "Button 1" ) )
        {
            ImGui::Text("Button 1");
        }

        ImGui::SameLine();

        if ( ImGui::Button( "Button 2" ) )
        {
            ImGui::Text("Button 2");
        }

    }
    ImGui::End();

}
