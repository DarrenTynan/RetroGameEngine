//
// Created by Darren Tynan on 06/01/2025.
//

#include "../include/Editor.h"

#if !SDL_VERSION_ATLEAST(2,0,17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

namespace EDITOR
{
    SDL_Window *editorWindow;
    SDL_Renderer *editorRenderer;

    SDL_Window *gameWindow;
    SDL_Renderer *gameRenderer;

    /**
     * @brief Setup the main sdl window.
     */
    void Editor::SetupSDL()
    {
        // Setup SDL
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
            std::cout << "SDL could not be initialised\n" << SDL_GetError();
            LOGGER::Logger::Error2Arg("SDL could not be initialised ", SDL_GetError());
            exit(1);
        }

        // Setup true type fonts
        if (TTF_Init() != 0)
        {
            LOGGER::Logger::Error("Error initializing SDL TTF");
            exit(1);
        }

        // From 2.0.18: Enable native IME.
        #ifdef SDL_HINT_IME_SHOW_UI
            SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
        #endif

        LOGGER::Logger::Log("SDL is ready to go!");

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
            LOGGER::Logger::Error("Window init failed");
            SDL_Quit();
            exit(1);
        }

        editorRenderer = SDL_CreateRenderer(editorWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        if (!editorRenderer)
        {
            LOGGER::Logger::Error("Window renderer init failed");
            SDL_DestroyRenderer(editorRenderer);
            SDL_Quit();
            exit(1);
        }

    }


    /**
     * @brief Load up pointers to display classes.
     */
//    void Editor::CreateDisplays()
//    {
//        // DisplayHolder is a struct in IDisplay.
//        // std::vector< std::unique_ptr<IDisplay> > displays;
//        auto pDisplayHolder = std::make_shared<DisplayHolder>();
//
//        // Instantiate the display windows via magic pointers
//        auto pMainMenuBar = std::make_unique<MainMenuBar>();
//        auto pTestDisplayA = std::make_unique<TestDisplayA>();
//        auto pTestDisplayB = std::make_unique<TestDisplayB>();
//        auto pSceneDisplay = std::make_unique<SceneDisplay>();
//        auto pLogDisplay = std::make_unique<LogDisplay>();
//
//        // Add display class's to the vector array in IDisplay
//        pDisplayHolder->displays.push_back( std::move(pMainMenuBar) );
//        pDisplayHolder->displays.push_back( std::move(pTestDisplayA) );
//        pDisplayHolder->displays.push_back( std::move(pTestDisplayB) );
//        pDisplayHolder->displays.push_back( std::move(pSceneDisplay) );
//        pDisplayHolder->displays.push_back( std::move(pLogDisplay) );
//
////        for ( const auto& pDisplay : pDisplayHolder->displays )
////        {
////            pDisplay->Draw();
////        }
//
//    }


    /**
     * @brief Initial setup of ImGui
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
//    ImGui::StyleColorsLight();

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
//    style.Colors[ImGuiCol_WindowBg]              = ImVec4(0.09f, 0.09f, 0.15f, 1.00f);
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
        // std::vector< std::unique_ptr<IDisplay> > displays;
        auto pDisplayHolder = std::make_shared<DisplayHolder>();

        // Instantiate the display windows via magic pointers
        auto pMainMenuBar = std::make_unique<MainMenuBar>();
        auto pTestDisplayA = std::make_unique<TestDisplayA>();
        auto pTestDisplayB = std::make_unique<TestDisplayB>();
        auto pSceneDisplay = std::make_unique<SceneDisplay>();
        auto pLogDisplay = std::make_unique<LogDisplay>();

        // Add display class's to the vector array in IDisplay
        pDisplayHolder->displays.push_back( std::move(pMainMenuBar) );
        pDisplayHolder->displays.push_back( std::move(pTestDisplayA) );
        pDisplayHolder->displays.push_back( std::move(pTestDisplayB) );
        pDisplayHolder->displays.push_back( std::move(pSceneDisplay) );
        pDisplayHolder->displays.push_back( std::move(pLogDisplay) );

        // Main loop
        bool done = false;
        while (!done)
        {
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                ImGui_ImplSDL2_ProcessEvent(&event);
                if (event.type == SDL_QUIT)
                    done = true;
                if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE &&
                    event.window.windowID == SDL_GetWindowID(editorWindow))
                    done = true;
            }
            if (SDL_GetWindowFlags(editorWindow) & SDL_WINDOW_MINIMIZED)
            {
                SDL_Delay(10);
                continue;
            }

            // Start the Dear ImGui frame
            ImGui_ImplSDLRenderer2_NewFrame();
            ImGui_ImplSDL2_NewFrame();
            ImGui::NewFrame();

            // Set docking to main viewport
            ImGui::DockSpaceOverViewport();

            // Draw the editor display panels.
            for ( const auto& pDisplay : pDisplayHolder->displays )
            {
                pDisplay->Draw();
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
        }
    }


    /**
     * Poll window events:
     *
     * window quit
     * keyboard
     */
    bool Editor::ProcessDebugInputEvents()
    {
        bool isRunning = true;

        SDL_Event sdlEvent;
        while (SDL_PollEvent(&sdlEvent))
        {
            // ImGui
            ImGui_ImplSDL2_ProcessEvent(&sdlEvent);
            ImGuiIO io = ImGui::GetIO();
            int mouseX;
            int mouseY;
            const unsigned int buttons = SDL_GetMouseState(&mouseX, &mouseY);
            io.MousePos = ImVec2((float) mouseX, (float) mouseY);
            io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
            io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);

            // Core sdl events.
            switch (sdlEvent.type)
            {
                // Window close
                case SDL_QUIT:
                    isRunning = false;
                    break;

                case SDL_KEYDOWN:
                    if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
                    { isRunning = false; }
                    break;

                    // Check for window event
                case SDL_WINDOWEVENT:

                    switch (sdlEvent.window.event)
                    {
                        case SDL_WINDOWEVENT_CLOSE:
                            isRunning = false;
                            break;
                    }
                    break;
            }
        };
        return isRunning;
    };


    /**
     * @brief Game Loop
     */
    void Editor::Run()
    {
        bool isGameRunning = true;
        while (isGameRunning)
        {
            isGameRunning = Editor::ProcessDebugInputEvents();
        }
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

