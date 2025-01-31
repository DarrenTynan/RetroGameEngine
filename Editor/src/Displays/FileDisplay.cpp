//
// Created by Darren Tynan on 24/01/2025.
//

#include "FileDisplay.h"

EDITOR::FileDisplay::FileDisplay()
{
    nodes = EDITOR_FILEDIALOG::FileDialogs::GetInstance()->GetFolderTree();
}

void EDITOR::FileDisplay::Render()
{
    if ( ImGui::Begin( "File System" ) )
    {
        ImGuiTreeNodeFlags flag = ImGuiTreeNodeFlags_DefaultOpen;
        auto rootName = nodes[0];
        rootName = rootName.substr(6);

        if (ImGui::TreeNodeEx(rootName.c_str(), flag))
        {
            for (auto i : nodes)
            {
                i = i.substr(6);
                ImGui::Text("%s", i.c_str());
            }

            ImGui::TreePop();  // This is required at the end of the if block
        }
    }
    // ***********
    NodeTree();
    // ***********

    ImGui::End();

}

void EDITOR::FileDisplay::GetFolderTree()
{
    ImGuiTreeNodeFlags flag = ImGuiTreeNodeFlags_DefaultOpen;

    std::string folderPtr = "../../Game_Editor";

    for (const auto & entry : std::filesystem::recursive_directory_iterator(folderPtr))
    {

        if (ImGui::TreeNodeEx(folderPtr.c_str(), flag))
        {
            for (auto i : nodes)
            {
                i = i.substr(6);
                ImGui::Text("%s", i.c_str());
            }

            ImGui::TreePop();  // This is required at the end of the if block
        }
    }

}


// Helper to display a little (?) mark which shows a tooltip when hovered.
// In your own code you may want to display an actual icon if you are using a merged icon fonts (see docs/FONTS.md)
static void HelpMarker(const char* desc)
{
    ImGui::TextDisabled("(?)");
    if (ImGui::BeginItemTooltip())
    {
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

void EDITOR::FileDisplay::NodeTree()
{
    const float TEXT_BASE_WIDTH = 11.0f;
    if (ImGui::TreeNode("Tree view"))
    {
        static ImGuiTableFlags flags = ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersOuterH | ImGuiTableFlags_Resizable | ImGuiTableFlags_RowBg | ImGuiTableFlags_NoBordersInBody;

        static ImGuiTreeNodeFlags tree_node_flags = ImGuiTreeNodeFlags_SpanAllColumns;
        ImGui::CheckboxFlags("ImGuiTreeNodeFlags_SpanFullWidth",  &tree_node_flags, ImGuiTreeNodeFlags_SpanFullWidth);
        ImGui::CheckboxFlags("ImGuiTreeNodeFlags_SpanTextWidth",  &tree_node_flags, ImGuiTreeNodeFlags_SpanTextWidth);
        ImGui::CheckboxFlags("ImGuiTreeNodeFlags_SpanAllColumns", &tree_node_flags, ImGuiTreeNodeFlags_SpanAllColumns);

        HelpMarker("See \"Columns flags\" section to configure how indentation is applied to individual columns.");
        if (ImGui::BeginTable("3ways", 3, flags))
        {
            // The first column will use the default _WidthStretch when ScrollX is Off and _WidthFixed when ScrollX is On
            ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_NoHide);
            ImGui::TableSetupColumn("Size", ImGuiTableColumnFlags_WidthFixed, TEXT_BASE_WIDTH * 12.0f);
            ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_WidthFixed, TEXT_BASE_WIDTH * 18.0f);
            ImGui::TableHeadersRow();

            // Simple storage to output a dummy file-system.
            struct MyTreeNode
            {
                const char*     Name;
                const char*     Type;
                int             Size;
                int             ChildIdx;
                int             ChildCount;
                static void DisplayNode(const MyTreeNode* node, const MyTreeNode* all_nodes)
                {
                    ImGui::TableNextRow();
                    ImGui::TableNextColumn();
                    const bool is_folder = (node->ChildCount > 0);
                    if (is_folder)
                    {
                        bool open = ImGui::TreeNodeEx(node->Name, tree_node_flags);
                        ImGui::TableNextColumn();
                        ImGui::TextDisabled("--");
                        ImGui::TableNextColumn();
                        ImGui::TextUnformatted(node->Type);
                        if (open)
                        {
                            for (int child_n = 0; child_n < node->ChildCount; child_n++)
                                DisplayNode(&all_nodes[node->ChildIdx + child_n], all_nodes);
                            ImGui::TreePop();
                        }
                    }
                    else
                    {
                        ImGui::TreeNodeEx(node->Name, tree_node_flags | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet | ImGuiTreeNodeFlags_NoTreePushOnOpen);
                        ImGui::TableNextColumn();
                        ImGui::Text("%d", node->Size);
                        ImGui::TableNextColumn();
                        ImGui::TextUnformatted(node->Type);
                    }
                }
            };
            static const MyTreeNode nodes[] =
                    {
                            { "Root",                         "Folder",       -1,       1, 3    }, // 0
                            { "Music",                        "Folder",       -1,       4, 2    }, // 1
                            { "Textures",                     "Folder",       -1,       6, 3    }, // 2
                            { "desktop.ini",                  "System file",  1024,    -1,-1    }, // 3
                            { "File1_a.wav",                  "Audio file",   123000,  -1,-1    }, // 4
                            { "File1_b.wav",                  "Audio file",   456000,  -1,-1    }, // 5
                            { "Image001.png",                 "Image file",   203128,  -1,-1    }, // 6
                            { "Copy of Image001.png",         "Image file",   203256,  -1,-1    }, // 7
                            { "Copy of Image001 (Final2).png","Image file",   203512,  -1,-1    }, // 8
                    };

            MyTreeNode::DisplayNode(&nodes[0], nodes);

            ImGui::EndTable();
        }
        ImGui::TreePop();
    }

}

