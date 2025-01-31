//
// Created by Darren Tynan on 21/01/2025.
//

#include "../FileSystem/include/FileDialogs.h"
#include "../libs/tinyfiledialogs/tinyfiledialogs.h"
#include "../libs/tinyfiledialogs/tinyfiledialogs.c"
#include "../Logger/include/Logger.h"
#include <string>
#include <vector>
#include <iostream>

namespace EDITOR_FILEDIALOG
{
    /**
     * even though I've defined the static member variable outside the class,
     * it remains inaccessible directly because it's still declared as private
     * within the class. The purpose of defining it outside the class is to
     * allocate memory for it, but its access is still controlled by the class's
     * access specifiers.
    */
    FileDialogs* FileDialogs::instancePtr = nullptr;


    std::string FileDialogs::OpenFileDialog2( const std::string& sTitle, const std::string& sDefaultPath,
                                            const std::vector<const char*>& filters, const std::string& sFilterDesc )
    {
        const char* file = tinyfd_openFileDialog(
                sTitle.c_str(), sDefaultPath.c_str(), filters.size(),
                filters.data(), sFilterDesc.c_str(), 0 );

        if ( !file )
            return std::string{};

        return std::string{ file };
    }

    std::string FileDialogs::SaveFileDialog2( const std::string& sTitle, const std::string& sDefaultPath,
                                            const std::vector<const char*>& filters, const std::string& sFilterDesc )
    {
        const char* file = tinyfd_saveFileDialog(
                sTitle.c_str(), sDefaultPath.c_str(), filters.size(), filters.data(), sFilterDesc.c_str() );

        if ( !file )
            return std::string{};

        return std::string{ file };
    }

    std::string FileDialogs::SelectFolderDialog2( const std::string& sTitle, const std::string& sDefaultPath )
    {
        const char* folder = tinyfd_selectFolderDialog( sTitle.c_str(), sDefaultPath.c_str() );

        if ( !folder )
            return std::string{};

        try
        {
            std::string folderName = "Game_Editor";
            // Create folder New Game
            std::filesystem::create_directories(std::string{folder} + folderName );
            std::filesystem::create_directories(std::string{folder} + folderName + "/assets" );
            std::filesystem::create_directories(std::string{folder} + folderName + "/include" );
            std::filesystem::create_directories(std::string{folder} + folderName + "/src" );
            std::filesystem::create_directories(std::string{folder} + folderName + "/scripts" );
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }

        return std::string{ folder } + "Game_Editor";
    }



    void FileDialogs::NewProjectDialog()
    {
        // TODO
    }


    /**
     * @brief Open the file picker window
     */
    void FileDialogs::OpenFileDialog()
    {
        NFD_Init();

        nfdu8char_t *outPath;
        nfdu8filteritem_t filters[2] = { { "Source code", "c,cpp,cc" }, { "Headers", "h,hpp" } };
        nfdopendialogu8args_t args = {0};
        args.filterList = filters;
        args.filterCount = 2;
        nfdresult_t result = NFD_OpenDialogU8_With(&outPath, &args);
        if (result == NFD_OKAY)
        {
            puts("Success!");
            puts(outPath);
            NFD_FreePathU8(outPath);
        }
        else if (result == NFD_CANCEL)
        {
            puts("User pressed cancel.");
        }
        else
        {
            printf("Error: %s\n", NFD_GetError());
        }

        NFD_Quit();
    }


    void FileDialogs::SaveDialog()
    {
        // TODO
    }


    void FileDialogs::SelectFolderDialog()
    {
        // TODO
    }

    std::vector<std::string> FileDialogs::GetFolderTree()
    {
        auto logger = EDITOR_LOGGER::Logger::GetInstance();

        std::string folderPtr = "../../Game_Editor";

//        for (const auto & entry : std::filesystem::directory_iterator(folderPtr))
//        {
//            std::cout << entry.path() << std::endl;
//        }

        // Create nodes folder ptr
        std::vector<std::string> nodes = {};
        // Add the root node
        nodes.push_back(folderPtr);

        for (const auto & entry : std::filesystem::recursive_directory_iterator(folderPtr))
        {
            std::cout << entry.path() << std::endl;


            std::string path = entry.path();
            std::string fullPath = path + '\n';
            logger->AddLog(fullPath.c_str());
            nodes.push_back(fullPath.c_str());
        }

        return nodes;
    }


}  // end namespace