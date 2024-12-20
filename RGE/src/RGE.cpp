//
// Created by Darren Tynan on 17/11/2024.
//

#include "../include/RGE.h"

#if !SDL_VERSION_ATLEAST(2,0,17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

/**
 * @brief Initial setup of the SDL and true type fonts
 *
 * @return true / false
 */
int RGE::setupSDL()
{
    // Setup SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "SDL could not be initialised\n" << SDL_GetError();
        Logger::Error2Arg("SDL could not be initialised ", SDL_GetError());
        return false;
    }

    // Setup true type fonts
    if (TTF_Init() != 0)
    {
        Logger::Error("Error initializing SDL TTF");
        return false;
    }

    // From 2.0.18: Enable native IME.
    #ifdef SDL_HINT_IME_SHOW_UI
        SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
    #endif

//    Logger::Log("SDL is ready to go!");

    return true;
}


/**
 * Setup game SDL window, renderer and camera
 *
 * @return true / false
 */
int RGE::setupRgeSDL()
{
    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);

    // Create window with SDL_Renderer graphics context
    auto windowFlags = (SDL_WindowFlags) (SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN | SDL_WINDOW_ALWAYS_ON_TOP);
    rgeWindow = SDL_CreateWindow(
            "Retro Game RGE v1",
            GAME_WINDOW_WIDTH,
            0,
            (displayMode.w - GAME_WINDOW_WIDTH),
            GAME_WINDOW_HEIGHT,
//            displayMode.h,
            windowFlags
    );

    if (!rgeWindow)
    {
        Logger::Error("Window init failed");
        SDL_Quit();
        return false;
    }

    rgeRenderer = SDL_CreateRenderer(rgeWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!rgeRenderer)
    {
        Logger::Error("Window renderer init failed");
        SDL_DestroyRenderer(rgeRenderer);
        SDL_Quit();
        return false;
    }

    // SetupSDL the camera view with the entire screen area
    rgeCamera = {0, 0, displayMode.w, displayMode.h};

    return true;
}


/**
 * @brief Setup game SDL window, renderer and camera
 *
 * @return -1 for errors
 */
int RGE::setupGameSDL()
{
    // Create window with SDL_Renderer graphics context
    auto windowFlags = (SDL_WindowFlags) (SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN | SDL_WINDOW_ALWAYS_ON_TOP);
    gameWindow = SDL_CreateWindow(
            "Game Window",
            0,
            0,
//            SDL_WINDOWPOS_CENTERED,
//            SDL_WINDOWPOS_CENTERED,
            GAME_WINDOW_WIDTH,
            GAME_WINDOW_HEIGHT,
            windowFlags
    );

    if (!gameWindow)
    {
        Logger::Error("Window init failed");
        SDL_Quit();
        return false;
    }

    gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!gameRenderer)
    {
        Logger::Error("Window renderer init failed");
        SDL_DestroyRenderer(gameRenderer);
        SDL_Quit();
        return false;
    }

    // SetupSDL the camera view with the entire screen area
    gameCamera = {0, 0, GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT};

    return true;
}


/**
 * @brief Initial setup of ImGui
 */
void RGE::setupImGui()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
//    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    io.Fonts->AddFontFromFileTTF("../RGE/include/Pixellettersfull.ttf", 16.f);

    // Setup Dear ImGui style
//    ImGui::StyleColorsDark();
    ImGui::StyleColorsLight();

    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 5.3f;
    style.FrameRounding = 2.3f;
    style.ScrollbarRounding = 0;

    style.Colors[ImGuiCol_Text]                  = ImVec4(0.90f, 0.90f, 0.90f, 0.90f);
    style.Colors[ImGuiCol_TextDisabled]          = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
    style.Colors[ImGuiCol_WindowBg]              = ImVec4(0.09f, 0.09f, 0.15f, 1.00f);
    style.Colors[ImGuiCol_ChildBg]               = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_PopupBg]               = ImVec4(0.05f, 0.05f, 0.10f, 0.85f);
    style.Colors[ImGuiCol_Border]                = ImVec4(0.70f, 0.70f, 0.70f, 0.65f);
    style.Colors[ImGuiCol_BorderShadow]          = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_FrameBg]               = ImVec4(0.00f, 0.00f, 0.01f, 1.00f);
    style.Colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.90f, 0.80f, 0.80f, 0.40f);
    style.Colors[ImGuiCol_FrameBgActive]         = ImVec4(0.90f, 0.65f, 0.65f, 0.45f);
    style.Colors[ImGuiCol_TitleBg]               = ImVec4(0.00f, 0.00f, 0.00f, 0.83f);
    style.Colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(0.40f, 0.40f, 0.80f, 0.20f);
    style.Colors[ImGuiCol_TitleBgActive]         = ImVec4(0.00f, 0.00f, 0.00f, 0.87f);
    style.Colors[ImGuiCol_MenuBarBg]             = ImVec4(0.01f, 0.01f, 0.02f, 0.80f);
    style.Colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.20f, 0.25f, 0.30f, 0.60f);
    style.Colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.55f, 0.53f, 0.55f, 0.51f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.56f, 0.56f, 0.56f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.56f, 0.56f, 0.56f, 0.91f);
    style.Colors[ImGuiCol_CheckMark]             = ImVec4(0.90f, 0.90f, 0.90f, 0.83f);
    style.Colors[ImGuiCol_SliderGrab]            = ImVec4(0.70f, 0.70f, 0.70f, 0.62f);
    style.Colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.30f, 0.30f, 0.30f, 0.84f);
    style.Colors[ImGuiCol_Button]                = ImVec4(0.48f, 0.72f, 0.89f, 0.49f);
    style.Colors[ImGuiCol_ButtonHovered]         = ImVec4(0.50f, 0.69f, 0.99f, 0.68f);
    style.Colors[ImGuiCol_ButtonActive]          = ImVec4(0.80f, 0.50f, 0.50f, 1.00f);
    style.Colors[ImGuiCol_Header]                = ImVec4(0.30f, 0.69f, 1.00f, 0.53f);
    style.Colors[ImGuiCol_HeaderHovered]         = ImVec4(0.44f, 0.61f, 0.86f, 1.00f);
    style.Colors[ImGuiCol_HeaderActive]          = ImVec4(0.38f, 0.62f, 0.83f, 1.00f);
    style.Colors[ImGuiCol_Separator]             = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    style.Colors[ImGuiCol_SeparatorHovered]      = ImVec4(0.70f, 0.60f, 0.60f, 1.00f);
    style.Colors[ImGuiCol_SeparatorActive]       = ImVec4(0.90f, 0.70f, 0.70f, 1.00f);
    style.Colors[ImGuiCol_ResizeGrip]            = ImVec4(1.00f, 1.00f, 1.00f, 0.85f);
    style.Colors[ImGuiCol_ResizeGripHovered]     = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
    style.Colors[ImGuiCol_ResizeGripActive]      = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
    style.Colors[ImGuiCol_PlotLines]             = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_PlotLinesHovered]      = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogram]         = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.00f, 0.00f, 1.00f, 0.35f);
    style.Colors[ImGuiCol_ModalWindowDimBg]      = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForSDLRenderer(rgeWindow, rgeRenderer);
    ImGui_ImplSDLRenderer2_Init(rgeRenderer);

}


/**
 * @brief Initialise the registry with systems.
 */
void RGE::setupSystemRegistry()
{
    // Add the systems that need to be processed in our game
    registry->AddSystem<PlayerControlSystem>();         // Read keys and control player movements.

//    registry->AddSystem<KeyboardControlSystem>();

    registry->AddSystem<MovementSystem>();              // Move all entities
    registry->AddSystem<AnimationSystem>();             // Animate all entities
    registry->AddSystem<CollisionSystem>();             // Check all entity collisions
    registry->AddSystem<DamageSystem>();                // Check all damage systems
    registry->AddSystem<CameraMovementSystem>();        // Check the camera move system
    registry->AddSystem<ProjectileEmitSystem>();        // Check entity bullets
    registry->AddSystem<ProjectileLifecycleSystem>();   // Check the life cycle and kill off bullets

    registry->AddSystem<RenderColliderSystem>();        // Debug render collision box's
    registry->AddSystem<RenderSystem>();                // Render windows
    registry->AddSystem<RenderTextSystem>();            // Render any label's
    registry->AddSystem<RenderImGuiSystem>();           // Render the engine window
    registry->AddSystem<RenderRaycastSystem>();         // Debug render the ray cast's

}


/**
 * @brief Call render on all objects
 */
void RGE::render()
{
    SDL_SetRenderDrawColor(rgeRenderer, (Uint8)(rge_clear_color.x * 255), (Uint8)(rge_clear_color.y * 255), (Uint8)(rge_clear_color.z * 255), (Uint8)(rge_clear_color.w * 255));
    SDL_RenderClear(rgeRenderer);

    SDL_SetRenderDrawColor(gameRenderer, (Uint8)(game_clear_color.x * 255), (Uint8)(game_clear_color.y * 255), (Uint8)(game_clear_color.z * 255), (Uint8)(game_clear_color.w * 255));
    SDL_RenderClear(gameRenderer);

    // Invoke all the systems that need to render
    registry->GetSystem<RenderSystem>().Update(gameRenderer, assetStore, gameCamera);
    registry->GetSystem<RenderTextSystem>().Update(gameRenderer, assetStore, gameCamera);
    registry->GetSystem<RenderImGuiSystem>().Update(registry, rgeCamera);

    if (isCollider)
    {
        registry->GetSystem<RenderColliderSystem>().Update(gameRenderer, gameCamera);
    }

    if (isRayCast)
    {
        auto player = registry->GetEntityByTag("player");
        registry->GetSystem<RenderRaycastSystem>().Update(gameRenderer, player);
    }

    // Display HUD
    SDL_Texture* hud = assetStore->GetTexture("hud2");
    SDL_Rect source = {0,0,800, 56};
    SDL_Rect destination = {0,600-56,800,56};

    SDL_RenderCopy(gameRenderer, hud, &source, &destination);
    SDL_RenderPresent(gameRenderer);

    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), rgeRenderer);
    SDL_RenderPresent(rgeRenderer);

}


/**
  * @brief Initialise the assetStore with pointers to png.
 */
void RGE::setupAssets()
{
    // Adding assets to the asset store
    assetStore->AddTexture(gameRenderer, "hud2", "../Game/assets/images/hud3.png");
    assetStore->AddFont("arial-font", "../Game/assets/fonts/arial.ttf", 24);
    assetStore->AddTexture(gameRenderer, "tilemap-image", "../Game/assets/tilemaps/TestLevel/TestLevel.png");

    // mapImagePath not correct
//    assetStore->AddTexture(gameRenderer, "tilemap-image", mapImagePath);
    assetStore->AddTexture(gameRenderer, "tank-image", "../Game/assets/images/tank-panther-right.png");
    assetStore->AddTexture(gameRenderer, "truck-image", "../Game/assets/images/truck-ford-right.png");
    assetStore->AddTexture(gameRenderer, "chopper-image", "../Game/assets/images/chopper.png");
    assetStore->AddTexture(gameRenderer, "player-idle-image", "../Game/assets/sprites/CharacterIdle.png");
    assetStore->AddTexture(gameRenderer, "bullet-image", "../Game/assets/images/bullet.png");
}


/**
* @brief Initialise the player object with components.
 */
void RGE::setupObjects()
{
    Entity player = registry->CreateEntity();
    player.AddTag("player");

    player.AddComponent<TransformComponent>(glm::vec2(256, 32*14), glm::vec2(1.0, 1.0), 0.0);
    player.AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0));
    player.AddComponent<BoxColliderComponent>(32, 32, glm::vec2(0,0));
    player.AddComponent<SpriteComponent>("player-idle-image", 32, 32, 1, false, false);
    player.AddComponent<AnimationComponent>(6, 8, true);
    player.AddComponent<PlayerControllerComponent>(glm::vec2(0, -80.0), glm::vec2(80.0, 0), glm::vec2(0, 80.0), glm::vec2(-80.0, 0));
    player.AddComponent<HealthComponent>(100);
    player.AddComponent<RaycastComponent>(glm::vec2(256, 256));

    std::cout << "DEBUG" << std::endl;
    std::cout << player.GetComponent<RigidBodyComponent>().fsm->isGrounded << std::endl;

    //    player.AddComponent<CameraFollowComponent>();
//    player.AddComponent<ProjectileEmitterComponent>(glm::vec2(150, 0), 1000, 1000, 10, false);


//    Entity tank = registry->CreateEntity();
//    tank.AddComponent<TransformComponent>(glm::vec2(100.0, 100.0), glm::vec2(2.0, 2.0), 0.0);
//    tank.AddComponent<RigidBodyComponent>(glm::vec2(20.0, 0.0));
//    tank.AddComponent<SpriteComponent>("tank-image", 32, 32, 1, false, 0, 0);
//    tank.AddComponent<BoxColliderComponent>(22, 22, glm::vec2(10,10));
//    tank.AddComponent<ProjectileEmitterComponent>(glm::vec2(150, 0), 1000, 1000, 10, false);

//    Entity label = registry->CreateEntity();
//    SDL_Color red = {255,0,0};
//    label.AddComponent<TextLabelComponent>(glm::vec2(200, 200), "This is a label", "arial-font", red, true);

}


/**
 * Load the tmx map files and iterate over.
 *
 * @return
 */
int RGE::setupTMX()
{
    map.load(MAP_PATH);

    if(map.load(MAP_PATH))
    {
        const auto& layers = map.getLayers();
        for(const auto& layer : layers)
        {
            // Get Object layer
            if(layer->getType() == tmx::Layer::Type::Object)
            {
                const auto& objectLayer = layer->getLayerAs<tmx::ObjectGroup>();
                const auto& objects = objectLayer.getObjects();
                for(const auto& object : objects)
                {
                    //do stuff with object properties
                    Entity tile = registry->CreateEntity();
                    tile.AddComponent<BoxColliderComponent>(object.getAABB().width, object.getAABB().height);
                    tile.AddComponent<TransformComponent>(glm::vec2(object.getAABB().left,  object.getAABB().top));
                    tile.AddTag("object");

                }
            }
                // Get Tile layer
            else if(layer->getType() == tmx::Layer::Type::Tile)
            {
                const auto& tileLayer = layer->getLayerAs<tmx::TileLayer>();
                //read out tile layer properties etc...

                const auto& tiles = layer->getLayerAs<tmx::TileLayer>().getTiles();

                const auto& imagePath = map.getTilesets();
                mapImagePath = imagePath[0].getImagePath();

                // Tile width in pixels (32)
                unsigned int tileWidth = map.getTileSize().x;
                // Tile height in pixels (32)
                unsigned int tileHeight = map.getTileSize().x;
                // Image width
                unsigned int imageWidth = map.getTilesets().size();

                // How many tiles per row (25)
                unsigned int tileCountX = map.getTileCount().x;
                mapWidth = map.getTileCount().x * tileWidth;
                // How many tiles per column (20)
                unsigned int tileCountY = map.getTileCount().y;
                mapHeight = map.getTileCount().y * tileHeight;

                int index = 0;
                for (int y = 0; y < tileCountY; y++) {
                    for (int x = 0; x < tileCountX; x++) {
                        // Get the source rect pixel x,y position.
                        int tilesPerRow = imagePath[0].getImageSize().x / tileWidth;
                        int firstgid = 1;
                        int srcRectX = ( (tiles[index].ID - firstgid) % tilesPerRow )  * tileWidth;
                        int srcRectY = ( (tiles[index].ID - firstgid) / tilesPerRow ) * tileHeight;

                        Entity tile = registry->CreateEntity();
                        tile.AddTag("tile");

                        tile.AddComponent<TransformComponent>(glm::vec2(x * tileWidth, y * tileHeight), glm::vec2(1, 1), 0.0);
                        tile.AddComponent<SpriteComponent>("tilemap-image", tileWidth, tileHeight, 0, true, false, srcRectX, srcRectY);
                        index++;
                    }
                }
            }
        }

//        const auto& tilesets = map.getTilesets();
//        for(const auto& tileset : tilesets)
//        {
//            Logger::Log(tileset.getImagePath());
//            read out tile set properties, load textures etc...
//        }
    }

    return 0;
}


/**
 * Poll window events:
 *
 * window quit
 * keyboard
 */
bool RGE::processInputEvents()
{
    bool isQuit = true;

    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent))
    {
        // ImGui
        ImGui_ImplSDL2_ProcessEvent(&sdlEvent);
        ImGuiIO io = ImGui::GetIO();
        int mouseX;
        int mouseY;
        const unsigned int buttons = SDL_GetMouseState(&mouseX, &mouseY);
        io.MousePos = ImVec2((float)mouseX, (float)mouseY);
        io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
        io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);

        if (sdlEvent.type == SDL_KEYUP)
        {
            eventBus->EmitEvent<KeyReleasedEvent>(sdlEvent.key.keysym.sym);
        }

        // Core sdl events.
        switch (sdlEvent.type)
        {
            // Window close
            case SDL_QUIT:
                isQuit = false;
                break;

            case SDL_KEYDOWN:
                if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) { isQuit = false; }
                if (sdlEvent.key.keysym.sym == SDLK_c) { isCollider = !isCollider; }
                if (sdlEvent.key.keysym.sym == SDLK_r) { isRayCast = !isRayCast; }

                eventBus->EmitEvent<KeyPressedEvent>(sdlEvent.key.keysym.sym);
                break;

            // Check for window event
            case SDL_WINDOWEVENT:

                switch (sdlEvent.window.event)
                {

                    case SDL_WINDOWEVENT_CLOSE:
                        isQuit = false;
                        break;
                }
                break;
        }
    };
    return isQuit;
};


/**
 * UpdateSystems
 */
void RGE::updateSystems()
{
    // The difference in ticks since the last frame, converted to seconds
    double deltaTime = (SDL_GetTicks() - millisecsPreviouseFrame) / 1000.0;

    // Store the "previous" frame time
    millisecsPreviouseFrame = SDL_GetTicks();

    // Reset all event handlers for the current frame
    eventBus->Reset();

    // Perform the subscription of the events for all systems
    registry->GetSystem<DamageSystem>().SubscribeToEvents(eventBus);
    registry->GetSystem<PlayerControlSystem>().SubscribeToEvents(eventBus);
    registry->GetSystem<ProjectileEmitSystem>().SubscribeToEvents(eventBus);

    // UpdateSystems the registry to process the entities that are waiting to be created/deleted
    registry->Update();

    registry->GetSystem<MovementSystem>().Update(deltaTime);            // apply velocity and check out of bounds.
    registry->GetSystem<AnimationSystem>().Update();
    registry->GetSystem<CollisionSystem>().Update(eventBus);
    registry->GetSystem<CameraMovementSystem>().Update(gameCamera);
    registry->GetSystem<ProjectileEmitSystem>().Update(registry);
    registry->GetSystem<ProjectileLifecycleSystem>().Update();
//    registry->GetSystem<StateMachineSystem>().Update();           // Update player fsm

}


/**
 * @brief Setup var and instantiate the FSM.
 */
void RGE::setupVars()
{
    registry = std::make_unique<Registry>();
    assetStore = std::make_unique<AssetStore>();
    eventBus = std::make_unique<EventBus>();

//    fsm = new FSM();
//    fsm->toggle();
//    fsm.toggle();
//    fsm.toggle();
//    fsm.toggle();

}


/**
 * Destroy
 */
void RGE::destroy()
{
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyWindow(rgeWindow);
    SDL_DestroyRenderer(rgeRenderer);

    SDL_DestroyRenderer(rgeRenderer);
    SDL_DestroyWindow(gameWindow);

    SDL_Quit();
}


