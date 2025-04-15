//
// Created by Darren Tynan on 31/01/2025.
//

#include "../include/FileHandler.h"

namespace EDITOR_FILEHANDLER
{
    /**
     * even though I've defined the static member variable outside the class,
     * it remains inaccessible directly because it's still declared as private
     * within the class. The purpose of defining it outside the class is to
     * allocate memory for it, but its access is still controlled by the class's
     * access specifiers.
    */
    FileHandler* FileHandler::instancePtr = nullptr;

//    void EDITOR_FILEHANDLER::FileHandler::OpenConfigFile()
//    {
//        std::ifstream myfile ("/Users/darren/Development/C++_Projects/RetroGameEditor/editorConfig.json");
//
//        // always check whether the file is open
//        if ( myfile.is_open() )
//        {
//            myfile >> mystring; // pipe file's content into stream
//            std::cout << mystring; // pipe stream's content to standard output
//        }
//    }

    // Create a Document object to hold the JSON data of the config file
//    rapidjson::Document editorConfig;
    rapidjson::Document EDITOR_FILEHANDLER::FileHandler::LoadConfigFile()
    {
        // Load the config file.
        std::ifstream configFile ("/Users/darren/Development/C++_Projects/RetroGameEditor/editorConfig.json");

        // Check if the file is open.
        if ( !configFile.is_open()) exit(1);

        // Read the entire file into a string
        std::string json((std::istreambuf_iterator<char>(configFile)), std::istreambuf_iterator<char>());

        // Create a Document object
        // to hold the JSON data
        rapidjson::Document editorConfig;

        // Parse the JSON data
        editorConfig.Parse(json.c_str());

        // Check for parse errors
        if (editorConfig.HasParseError())
        {
            std::cerr << "Error parsing JSON: " << editorConfig.GetParseError() << std::endl;
            exit(1);
        }

        // Access the data in the JSON document
        std::cout << editorConfig["window_title"].GetString() << std::endl;
        std::cout << editorConfig["version"].GetString() << std::endl;

        return editorConfig;
    }

} // end namespace
