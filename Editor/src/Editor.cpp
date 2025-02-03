//
// Created by Darren Tynan on 06/01/2025.
//

#include "../include/Editor.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../libs/rapidjson/document.h"
#include "../libs/rapidjson/prettywriter.h"
#include <cstdio>

#if !SDL_VERSION_ATLEAST(2,0,17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

namespace EDITOR
{
    SDL_Window *editorWindow;
    SDL_Renderer *editorRenderer;

    SDL_Window *sceneWindow;
    SDL_Renderer *sceneRenderer;

    /**
     * @brief Display the initial project window
     */
    void Editor::ProjectWindow()
    {
        // Setup SDL
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
            std::cout << "Project SDL could not be initialised\n" << SDL_GetError();
            exit(1);
        }

        LOGGER::TerminalLogger::Log("Project SDL is ready to go!");

        // Setup true type fonts
        if (TTF_Init() != 0)
        {
            LOGGER::TerminalLogger::Error("Error initializing SDL TTF", 0);
            exit(1);
        }

        TTF_Font *font = TTF_OpenFont("/Users/darren/Development/C++_Projects/RetroGameEngine/Editor/fonts/Pixellettersfull.ttf", 32);

        if ( !font )
        {
            std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
        }

        // Create window with SDL_Renderer graphics context
        auto windowFlags = (SDL_WindowFlags)(
                                                SDL_WINDOW_MOUSE_CAPTURE |
                                                SDL_WINDOW_ALLOW_HIGHDPI
                                                );
        SDL_DisplayMode displayMode;
        SDL_GetCurrentDisplayMode(0, &displayMode);

        sceneWindow = SDL_CreateWindow(
                "Project Select",
                (displayMode.w / 2) - 600 / 2,
                (displayMode.h / 2) - 400 / 2,
                600,
                400,
                windowFlags
        );

        if (!sceneWindow)
        {
            LOGGER::TerminalLogger::Error("Project Window init failed", 0);
            SDL_Quit();
            exit(1);
        }

        // Create the scene renderer.
        sceneRenderer = SDL_CreateRenderer(sceneWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        if (!sceneRenderer)
        {
            LOGGER::TerminalLogger::Error("Project Window renderer init failed", 0);
            SDL_DestroyRenderer(sceneRenderer);
            SDL_Quit();
            exit(1);
        }

        // Background color and clear screen
        SDL_SetRenderDrawColor(sceneRenderer, 0,0,0,255);
        SDL_RenderClear(sceneRenderer);

        // Create surface with rendered text and set color
        SDL_Color textColor = {255, 255, 255, 255};

        // Project name
        SDL_Surface *textSurface = TTF_RenderText_Solid(font, project_name.c_str(), textColor);

        if (!textSurface)
        {
            printf("Failed to create text surface: %s\n", TTF_GetError());
        }

        // Create texture from surface
        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(sceneRenderer, textSurface);

        if (!textTexture)
        {
            printf("Failed to create text texture: %s\n", SDL_GetError());
            exit(1);
        }

        // Render text
        SDL_Rect textRect = {150, 50, textSurface->w, textSurface->h}; // rectangle where the text is drawn
        SDL_RenderCopy(sceneRenderer, textTexture, nullptr, &textRect);


        // File path
        SDL_Surface *textSurface1 = TTF_RenderText_Solid(font, file_path.c_str(), textColor);

        if (!textSurface1)
        {
            printf("Failed to create text surface: %s\n", TTF_GetError());
        }

        // Create texture from surface
        SDL_Texture *textTexture1 = SDL_CreateTextureFromSurface(sceneRenderer, textSurface1);

        if (!textTexture1)
        {
            printf("Failed to create text texture: %s\n", SDL_GetError());
            exit(1);
        }

        // Render text
        SDL_Rect textRect1 = {150, 100, textSurface1->w, textSurface1->h}; // rectangle where the text is drawn
        SDL_RenderCopy(sceneRenderer, textTexture1, nullptr, &textRect1);


        // Setup the image
        if (IMG_Init(IMG_INIT_PNG) == 0) {
            std::cout << "Error SDL2_image Initialization";
            exit(1);
        }

        // Load the logo.png
        SDL_Surface* logoSurface = IMG_Load("/Users/darren/Development/C++_Projects/RetroGameEngine/Game_Editor/icon.png");
        if (logoSurface == nullptr) {
            std::cout << "Error loading image: " << IMG_GetError();
            exit(1);
        }

        SDL_Texture* logoTexture = SDL_CreateTextureFromSurface(sceneRenderer, logoSurface);
        if (logoTexture == nullptr) {
            std::cout << "Error creating texture";
            exit(1);
        }

        SDL_FreeSurface(logoSurface);

        SDL_Rect srcRect = { 0, 0, 80, 80 };
        SDL_Rect dstRect = { 50, 50, 80, 80 };

        SDL_RenderCopy(sceneRenderer, logoTexture, &srcRect, &dstRect);

        // Set the project box rect
        SDL_Rect boxRect;
        boxRect.x = 25;
        boxRect.y = 25;
        boxRect.w = 1150;
        boxRect.h = 150;

        // Set render color to blue ( rect will be rendered in this color )
        SDL_SetRenderDrawColor( sceneRenderer, 128, 128, 128, 255 );

        // Render rect
        SDL_RenderDrawRect( sceneRenderer, &boxRect );

        // Render the images to the screen
        SDL_RenderPresent(sceneRenderer);

        bool run = true;
        while (run)
        {
            SDL_Event e;
            while (SDL_PollEvent(&e))
            {
                switch (e.type)
                {
                    case SDL_QUIT:
                        SDL_Log("Quit event detected");
                        run = false;
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        run = mousePress(e.button);
                        break;
                }
            }
        }

        SDL_DestroyRenderer(sceneRenderer);
        SDL_DestroyWindow(sceneWindow);
        SDL_Quit();
    }


    /**
     * @brief Handle mouse button down events.
     *
     * @param b
     */
    bool Editor::mousePress(SDL_MouseButtonEvent& b){
        if(b.button == SDL_BUTTON_LEFT)
        {
            int xMouse = 0;
            int yMouse = 0;
            SDL_GetMouseState(&xMouse, &yMouse);
            if (yMouse >= 18 & yMouse <= 90 )
            {
                std::cout << "LMB" << std::endl;
                std::cout << yMouse << std::endl;
                return false;
            }
        }
        return true;
    }


    /**
     * @brief Setup the main sdl window.
     */
    void Editor::SetupSDL()
    {
        ///////////////////////////////////////////////
        // RapidJson example
        using namespace rapidjson;
        const char json[] = " { \"hello\" : \"world\", \"t\" : true , \"f\" : false, \"n\": null, \"i\":123, \"pi\": 3.1416, \"a\":[1, 2, 3, 4] } ";
        printf("Original JSON:\n %s\n", json);
        Document document;
        document.Parse(json);
        assert(document.IsObject());
        assert(document.HasMember("hello"));
        assert(document["hello"].IsString());
        printf("hello = %s\n", document["hello"].GetString());
        assert(document["t"].IsBool());
        printf("t = %s\n", document["t"].GetBool() ? "true" : "false");
        printf("n = %s\n", document["n"].IsNull() ? "null" : "?");
        assert(document["i"].IsNumber());

        // In this case, IsUint()/IsInt64()/IsUint64() also return true.
        assert(document["i"].IsInt());
        printf("i = %d\n", document["i"].GetInt());
        // Alternatively (int)document["i"]

        assert(document["pi"].IsNumber());
        assert(document["pi"].IsDouble());
        printf("pi = %g\n", document["pi"].GetDouble());
        // Using a reference for consecutive access is handy and faster.
        const Value& a = document["a"];
        assert(a.IsArray());
        for (SizeType i = 0; i < a.Size(); i++) // Uses SizeType instead of size_t
            printf("a[%d] = %d\n", i, a[i].GetInt());

        // RapidJson example end
        ///////////////////////////////////////////////

        // Setup SDL
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
            std::cout << "SDL could not be initialised\n" << SDL_GetError();
            LOGGER::TerminalLogger::Error2Arg("SDL could not be initialised ", SDL_GetError());
            exit(1);
        }

        // Setup true type fonts
        if (TTF_Init() != 0)
        {
            LOGGER::TerminalLogger::Error("Error initializing SDL TTF", 0);
            exit(1);
        }

        // From 2.0.18: Enable native IME.
        #ifdef SDL_HINT_IME_SHOW_UI
            SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
        #endif

        LOGGER::TerminalLogger::Log("SDL is ready to go!");

        SDL_DisplayMode displayMode;
        SDL_GetCurrentDisplayMode(0, &displayMode);

        // Create window with SDL_Renderer graphics context
        auto windowFlags = (SDL_WindowFlags)(
                SDL_WINDOW_RESIZABLE | SDL_WINDOW_MOUSE_CAPTURE | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_ALLOW_HIGHDPI);
        editorWindow = SDL_CreateWindow(
                "Retro Game Engine v1",
                0,
                0,
                displayMode.w,
                displayMode.h,
                windowFlags
        );

        if (!editorWindow)
        {
            LOGGER::TerminalLogger::Error("Window init failed", 0);
            SDL_Quit();
            exit(1);
        }

        editorRenderer = SDL_CreateRenderer(editorWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        if (!editorRenderer)
        {
            LOGGER::TerminalLogger::Error("Window renderer init failed", 0);
            SDL_DestroyRenderer(editorRenderer);
            SDL_Quit();
            exit(1);
        }

    }


    /**
     * @brief Initial setup of ImGui and display panels.
     */
    void Editor::SetupImGui()
    {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void) io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;        // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // enable docking

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();

        ImGuiStyle &style = ImGui::GetStyle();
        style.WindowRounding = 5.3f;
        style.FrameRounding = 2.3f;
        style.ScrollbarRounding = 0;

        style.Colors[ImGuiCol_Tab] = ImVec4(0.30f, 0.69f, 1.00f, 0.53f);
        style.Colors[ImGuiCol_TabHovered] = ImVec4(0.44f, 0.61f, 0.86f, 1.00f);
        style.Colors[ImGuiCol_TabActive] = ImVec4(0.38f, 0.62f, 0.83f, 1.00f);

        style.Colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.90f, 0.90f);
        style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
        style.Colors[ImGuiCol_WindowBg] = ImVec4(0.09f, 0.09f, 0.15f, 0.50f);
        style.Colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        style.Colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.10f, 0.85f);
        style.Colors[ImGuiCol_Border] = ImVec4(0.70f, 0.70f, 0.70f, 0.65f);
        style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        style.Colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.00f, 0.01f, 1.00f);
        style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.90f, 0.80f, 0.80f, 0.40f);
        style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.90f, 0.65f, 0.65f, 0.45f);
        style.Colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.83f);
        style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.40f, 0.40f, 0.80f, 0.20f);
        style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.00f, 0.00f, 0.87f);
        style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.01f, 0.01f, 0.02f, 0.80f);
        style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.25f, 0.30f, 0.60f);
        style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.55f, 0.53f, 0.55f, 0.51f);
        style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.56f, 1.00f);
        style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.91f);
        style.Colors[ImGuiCol_CheckMark] = ImVec4(0.90f, 0.90f, 0.90f, 0.83f);
        style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.70f, 0.70f, 0.70f, 0.62f);
        style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.30f, 0.30f, 0.30f, 0.84f);
        style.Colors[ImGuiCol_Button] = ImVec4(0.48f, 0.72f, 0.89f, 0.49f);
        style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.50f, 0.69f, 0.99f, 0.68f);
        style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.80f, 0.50f, 0.50f, 1.00f);
        style.Colors[ImGuiCol_Header] = ImVec4(0.30f, 0.69f, 1.00f, 0.53f);
        style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.44f, 0.61f, 0.86f, 1.00f);
        style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.38f, 0.62f, 0.83f, 1.00f);
        style.Colors[ImGuiCol_Separator] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
        style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.70f, 0.60f, 0.60f, 1.00f);
        style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.90f, 0.70f, 0.70f, 1.00f);
        style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.85f);
        style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
        style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
        style.Colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
        style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 0.00f, 1.00f, 0.35f);
        style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);

        // Setup Platform/Renderer backends
        ImGui_ImplSDL2_InitForSDLRenderer(editorWindow, editorRenderer);
        ImGui_ImplSDLRenderer2_Init(editorRenderer);

        io.Fonts->AddFontFromFileTTF("../fonts/Pixellettersfull.ttf", 18.f);

        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        // DisplayHolder is a struct in IDisplay.
        // std::vector< std::unique_ptr<IDisplay> > Displays;
        auto pDisplayHolder = std::make_shared<DisplayHolder>();

        // Instantiate the display windows via magic pointers
        auto pMainMenuBar = std::make_unique<MainMenuBar>();
        auto pTestDisplayA = std::make_unique<TestDisplayA>();
        auto pTestDisplayB = std::make_unique<TestDisplayB>();
        auto pSceneDisplay = std::make_unique<SceneDisplay>();
        auto pLogDisplay = std::make_unique<LogDisplay>();
        auto pFileDisplay = std::make_unique<FileDisplay>();
//        auto pProjectMenuDisplay = std::make_unique<ProjectMenuDisplay>();

        // Add display class's to the vector array in IDisplay
        pDisplayHolder->displays.push_back( std::move(pMainMenuBar) );
        pDisplayHolder->displays.push_back( std::move(pTestDisplayA) );
        pDisplayHolder->displays.push_back( std::move(pTestDisplayB) );
        pDisplayHolder->displays.push_back( std::move(pSceneDisplay) );
        pDisplayHolder->displays.push_back( std::move(pLogDisplay) );
        pDisplayHolder->displays.push_back( std::move(pFileDisplay) );
//        pDisplayHolder->displays.push_back( std::move(pProjectMenuDisplay) );

        auto logger = EDITOR_LOGGER::Logger::GetInstance();
        logger->Clear();
        logger->AddLog("All systems should be up and running...\n");

        // Main render loop
        bool isRunning = true;
        while (isRunning)
        {
            // Start the Dear ImGui frame
            ImGui_ImplSDLRenderer2_NewFrame();
            ImGui_ImplSDL2_NewFrame();
            ImGui::NewFrame();

            // Set docking to main viewport
            ImGui::DockSpaceOverViewport();

            // Render the editor display panels.
            for ( const auto& pDisplay : pDisplayHolder->displays )
            {
                pDisplay->Render();
            }

            ImGui::ShowDemoWindow();

            // Rendering
            ImGui::Render();
            SDL_RenderSetScale(editorRenderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
            SDL_SetRenderDrawColor(editorRenderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255),
                                   (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
            SDL_RenderClear(editorRenderer);
            ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), editorRenderer);
            SDL_RenderPresent(editorRenderer);

            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                ImGui_ImplSDL2_ProcessEvent(&event);
                if (event.key.keysym.sym == SDLK_d)
                {
                    LOGGER::TerminalLogger::Error("EDITOR.cpp - event.SDLK_d - debug", 0);
                }
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    LOGGER::TerminalLogger::Error("EDITOR.cpp - event.SDLK_ESCAPE - debug", 0);
                    isRunning = false;
                }
                if (event.type == SDL_QUIT)
                {
                    LOGGER::TerminalLogger::Error("EDITOR.cpp - event.SDL_QUIT - debug", 0);
                    isRunning = false;
                }
                if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE &&
                    event.window.windowID == SDL_GetWindowID(editorWindow))
                {
                    LOGGER::TerminalLogger::Error("EDITOR.cpp - event.SDL_WINDOW_CLOSE - debug", 0);
                    isRunning = false;
                }

            }
        }
    }


    /**
     * @brief Editor Setup vars
     */
    void Editor::Setup()
    {
        // Instantiate instance
        auto logger = EDITOR_LOGGER::Logger::GetInstance();
        EDITOR_LOGGER::Logger::TestLog();

        // Load the config file
        auto fh = EDITOR_FILEHANDLER::FileHandler::GetInstance();
        fh->LoadConfigFile();
        this->project_name = fh->doc["configuration"]["project_name"].GetString();
        this->file_path = fh->doc["configuration"]["file_path"].GetString();
        this->window_width = fh->doc["configuration"]["window_width"].GetInt();
        this->window_height = fh->doc["configuration"]["window_height"].GetInt();
        this->window_title = fh->doc["configuration"]["window_title"].GetString();

        Editor::ProjectWindow();

        Editor::SetupSDL();
        Editor::SetupImGui();
    }


    /**
     * @brief Game Loop
     */
    void Editor::Run()
    {
        // TODO
        std::cout << "Run" << std::endl;
    }


    /**
     * @brief End all processes
     */
    void Editor::Destroy()
    {
        ImGui_ImplSDLRenderer2_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();

        SDL_DestroyWindow(editorWindow);
        SDL_DestroyRenderer(editorRenderer);

        SDL_Quit();

    }


} // namespace end

