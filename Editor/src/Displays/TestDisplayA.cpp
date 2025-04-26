//
// Created by Darren Tynan on 11/01/2025.
//

#include "TestDisplayA.h"
#include "../../Editor/libs/nativefiledialog-extended/src/include/nfd.h"

namespace EDITOR_DISPLAY
{

    TestDisplayA::TestDisplayA() = default;

    void TestDisplayA::Render(std::shared_ptr<Registry>& registry)
    {
        if (ImGui::Begin("Test Window A"))
        {
            if (ImGui::Button("Button 1"))
            {
                ImGui::Text("Button 1");
            }

            ImGui::SameLine();

            if (ImGui::Button("Button 2"))
            {
                ImGui::Text("Button 2");
            }

        }
        ImGui::End();

    }
} // end namespace