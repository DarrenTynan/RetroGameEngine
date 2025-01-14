//
// Created by Darren Tynan on 11/01/2025.
//

#include "TestDisplayB.h"

EDITOR::TestDisplayB::TestDisplayB() {}

void EDITOR::TestDisplayB::Draw()
{
    if ( ImGui::Begin( "Test Window B" ) )
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
