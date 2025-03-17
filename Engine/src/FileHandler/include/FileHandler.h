//
// Created by Darren Tynan on 30/01/2025.
//

#ifndef EDITOR_FILEHANDLER_H
#define EDITOR_FILEHANDLER_H

#include <iostream>
#include <fstream>
#include <string>
#include "../libs/rapidjson/document.h"
#include "../libs/rapidjson/prettywriter.h"

namespace RGE_FILEHANDLER
{
    class FileHandler
    {
    private:
        // Private constructor to prevent direct instantiation
        FileHandler() {}

        // Disable copy constructor and assignment operator
        FileHandler(const FileHandler&) = delete;
        FileHandler& operator=(const FileHandler&) = delete;

        // Private static instance
        static FileHandler* instancePtr;

    public:
        // Public static method to get instance
        static FileHandler* GetInstance()
        {
            if (instancePtr == nullptr)
            {
                instancePtr = new FileHandler();
            }
            return instancePtr;
        }


        std::string mystring{};
        rapidjson::Document doc;

        void OpenConfigFile();

        int LoadConfigFile(const std::string& path);
    };
} // end namespace
#endif //EDITOR_FILEHANDLER_H
