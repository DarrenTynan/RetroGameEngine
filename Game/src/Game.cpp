//
// Created by Darren Tynan on 17/11/2024.
//

#include "../include/Game.h"

#if !SDL_VERSION_ATLEAST(2,0,17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

Game::Game() { Logger::Log("Game constructor called"); }

Game::~Game() { Logger::Log("Game deconstruct called"); }

void Game::RenderTree()
{
    SDL_Surface* surface = IMG_Load("../Game/assets/images/tree.png");

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    SDL_Rect source;
    source.x = 0;
    source.y = 0;
    source.w = 16;
    source.h = 32;

    SDL_Rect destination;
    destination.x = 100;
    destination.y = 100;
    destination.w = 16*2;
    destination.h = 32*2;

    SDL_RenderCopy(renderer, texture, &source, &destination);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture);

}


/**
 * Initialise game objects
 */
void Game::SetUpGameObjects()
{
}


/**
 * Initialize SDL, DisplayMode, Window, Camera, ImGui
 *
 * @return -1 for errors
 */
int Game::Initialize()
{
    // Setup SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        std::cout << "SDL could not be initialised\n" << SDL_GetError();
        Logger::Error2Arg("SDL could not be initialised ", SDL_GetError());
        return -1;
    }

    // Setup true type fonts
    if (TTF_Init() != 0)
    {
        Logger::Error("Error initializing SDL TTF");
        return -1;
    }

    // From 2.0.18: Enable native IME.
    #ifdef SDL_HINT_IME_SHOW_UI
        SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
    #endif

    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    windowWidth = 1280;
    windowHeight = 720;
//    windowWidth = displayMode.w;
//    windowHeight = displayMode.h;

    // Create window with SDL_Renderer graphics context
    SDL_WindowFlags windowFlags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
    Game::window = SDL_CreateWindow(
            "Game",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            windowWidth,
            windowHeight,
            windowFlags
    );

    if (!window)
    {
        Logger::Error("Window init failed");
        return -1;
    }

    Game::renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer)
    {
        Logger::Error("Window renderer init failed");
        return -1;
    }

    Logger::Log("SDL is ready to go!");

    // Initialize the camera view with the entire screen area
    camera.x = 0;
    camera.y = 0;
    camera.w = windowWidth;
    camera.h = windowHeight;

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
//    ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != nullptr);

    // Set game running on
    isRunning = true;

    return 0;
}

/**
 * Main loop
 */
void Game::Run()
{
    SetUpGameObjects();

    while (isRunning)
    {
//        ProcessInput();
        UpdateSystems();
        Render();
        RenderImGui();
    }
}


/**
 * UpdateSystems
 */
void Game::UpdateSystems()
{
    int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks64() - millisecsPreviouseFrame);
    if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME) {
        SDL_Delay(timeToWait);
    }

    // The difference in ticks since the last frame, converted to seconds
    double deltaTime = (SDL_GetTicks() - millisecsPreviouseFrame) / 1000.0;

    millisecsPreviouseFrame = SDL_GetTicks();

    // Reset all event handlers for the current frame
//    eventBus->Reset();

    // Perform the subscription of the events for all systems
//    registry->GetSystem<DamageSystem>().SubscribeToEvents(eventBus);
//    registry->GetSystem<PlayerControlSystem>().SubscribeToEvents(eventBus);
//    registry->GetSystem<ProjectileEmitSystem>().SubscribeToEvents(eventBus);

    // UpdateSystems the registry to process the entities that are waiting to be created/deleted
//    registry->Update();

//    registry->GetSystem<MovementSystem>().Update(deltaTime);
//    registry->GetSystem<AnimationSystem>().Update();
//    registry->GetSystem<CollisionSystem>().Update(eventBus);
//    registry->GetSystem<CameraMovementSystem>().Update(camera);
//    registry->GetSystem<ProjectileEmitSystem>().Update(registry);
//    registry->GetSystem<ProjectileLifecycleSystem>().Update();

    RenderTree();
};


void Game::Destroy()
{
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


void Game::RenderImGui()
{
    // Our state
    bool done = false;
    bool show_demo_window = true;
    bool show_another_window = false;

    // Poll and handle events (inputs, window resize, etc.)
    // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
    // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
    // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
    // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL2_ProcessEvent(&event);
        if (event.type == SDL_QUIT)isRunning = false;
        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
            isRunning = false;
    }
    if (SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED)
    {
        SDL_Delay(10);
    }

    // Start the Dear ImGui frame
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
        ImGui::Checkbox("Another Window", &show_another_window);

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

//            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::End();
    }

    // 3. Show another simple window.
    if (show_another_window)
    {
        ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Hello from another window!");
        if (ImGui::Button("Close Me"))
            show_another_window = false;
        ImGui::End();
    }

    // Rendering
    ImGui::Render();
//        SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
    SDL_SetRenderDrawColor(renderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
    SDL_RenderClear(renderer);
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
    SDL_RenderPresent(renderer);

}


void Game::Render()
{
    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
//    SDL_SetRenderDrawColor(renderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
    SDL_RenderClear(renderer);

    // Invoke all the systems that need to render
//    registry->GetSystem<RenderSystem>().Update(renderer, assetStore, camera);
//    registry->GetSystem<RenderTextSystem>().Update(renderer, assetStore, camera);

//    if (isDebug) {
//        registry->GetSystem<RenderColliderSystem>().Update(renderer, camera);
//        auto player = registry->GetEntityByTag("player");
//        registry->GetSystem<RenderRaycastSystem>().Update(renderer, player);
//    }

//    if (isImGui) {
//        registry->GetSystem<RenderImGuiSystem>().Update(registry, camera);
//    }

    // Display HUD
//    SDL_Texture* hud = assetStore->GetTexture("hud");
//    SDL_Rect source;
//    source.x = 0;
//    source.y = 0;
//    source.w = 640;
//    source.h = 64;
//
//    SDL_Rect destination;
//    destination.x = 0;
//    destination.y = 480-64;
//    destination.w = 640;
//    destination.h = 64;
//
//    SDL_RenderCopy(renderer, hud, &source, &destination);
//
//    SDL_RenderPresent(renderer);

    // Display HUD
//    SDL_Texture* tree =  assetStore->GetTexture("hud");
//    SDL_Rect source;
//    source.x = 0;
//    source.y = 0;
//    source.w = 640;
//    source.h = 64;
//
//    SDL_Rect destination;
//    destination.x = 0;
//    destination.y = 480-64;
//    destination.w = 640;
//    destination.h = 64;
//
//    SDL_RenderCopy(renderer, hud, &source, &destination);
//
//    SDL_RenderPresent(renderer);
}

