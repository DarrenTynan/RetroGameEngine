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

    void EDITOR_FILEHANDLER::FileHandler::OpenConfigFile()
    {
        std::ifstream myfile ("/Users/darren/Development/C++_Projects/RetroGameEngine/Game_Editor/project.rge");

        // always check whether the file is open
        if ( myfile.is_open() )
        {
            myfile >> mystring; // pipe file's content into stream
            std::cout << mystring; // pipe stream's content to standard output
        }
    }

    int EDITOR_FILEHANDLER::FileHandler::LoadConfigFile()
    {
        // Open the file
        std::ifstream file("/Users/darren/Development/C++_Projects/RetroGameEngine/Game_Editor/project.rge");

        // Read the entire file into a string
        std::string json((std::istreambuf_iterator<char>(file)),
                    std::istreambuf_iterator<char>());

        // Create a Document object
        // to hold the JSON data
//        rapidjson::Document doc;

        // Parse the JSON data
        doc.Parse(json.c_str());

        // Check for parse errors
        if (doc.HasParseError()) {
            std::cerr << "Error parsing JSON: "
                 << doc.GetParseError() << std::endl;
            return 1;
        }

        // Access the data in the JSON document
        std::cout << doc["configuration"]["project_name"].GetString() << std::endl;
        std::cout << doc["configuration"]["file_path"].GetString() << std::endl;
//        std::cout << doc["age"].GetInt() << std::endl;
        // Now you can use the Document object to access the
        // JSON data
        return 0;
    }

} // end namespace
