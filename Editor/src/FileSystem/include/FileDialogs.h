//
// Created by Darren Tynan on 21/01/2025.
//

#ifndef EDITOR_FILEDIALOGS_H
#define EDITOR_FILEDIALOGS_H

#include <string>
#include <cstdio>
#include <filesystem>
#include <iostream>
#include "../libs/nativefiledialog-extended/src/include/nfd.h"
#include "../libs/tinyfiledialogs/tinyfiledialogs.h"

namespace EDITOR_FILEDIALOG
{
    class FileDialogs
    {
    private:
        // Private constructor to prevent instantiation
        FileDialogs() {}

        // Disable copy constructor and assignment operator
        FileDialogs(const FileDialogs&) = delete;
        FileDialogs& operator=(const FileDialogs&) = delete;

        // Private static instance
        static FileDialogs* instancePtr;

    public:
        // Public static method to get instance
        static FileDialogs* GetInstance()
        {
            if (instancePtr == nullptr)
            {
                instancePtr = new FileDialogs();
            }
            return instancePtr;
        }

        void NewProjectDialog();
        void OpenFileDialog();
        void SaveDialog();
        void SelectFolderDialog();

        std::string OpenFileDialog2( const std::string& sTitle, const std::string& sDefaultPath, const std::vector<const char*>& filters, const std::string& sFilterDesc );
        std::string SaveFileDialog2( const std::string& sTitle, const std::string& sDefaultPath, const std::vector<const char*>& filters, const std::string& sFilterDesc );
        std::string SelectFolderDialog2( const std::string& sTitle, const std::string& sDefaultPath );
        std::vector<std::string> GetFolderTree();
    };

}  // end namespace

#endif //EDITOR_FILEDIALOGS_H
