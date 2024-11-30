//
// Created by Darren Tynan on 17/11/2024.
//

#include "../include/Game.h"

#if !SDL_VERSION_ATLEAST(2,0,17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

const auto MAP_PATH = "../Game/assets/tilemaps/TestLevel/TestLevel.tmx";
//const auto MAP_PATH = "../Game/assets/tilemaps/Level_01.tmx";
std::string mapImagePath;
tmx::Map map;

Game::Game()
{
    registry = std::make_unique<Registry>();
    assetStore = std::make_unique<AssetStore>();
    eventBus = std::make_unique<EventBus>();
    Logger::Log("Game constructor called");
}

Game::~Game() { Logger::Log("Game deconstruct called"); }


/**
 * Test tree render
 */
void Game::RenderTree()
{
    temporarySurface = IMG_Load("../Game/assets/images/tree.png");
    temporaryTexture = SDL_CreateTextureFromSurface(gameRenderer, temporarySurface);
    SDL_FreeSurface(temporarySurface);

    SDL_Rect source;
    source.x = 0;
    source.y = 0;
    source.w = 16*4;
    source.h = 32*4;

    SDL_Rect destination;
    destination.x = 100;
    destination.y = 100;
    destination.w = 16*2;
    destination.h = 32*2;

    SDL_RenderCopy(gameRenderer, temporaryTexture, &source, &destination);
    SDL_RenderPresent(gameRenderer);
    SDL_DestroyTexture(temporaryTexture);

}


/**
 * Initialise the registry with systems.
 */
void Game::SetUpRegistry() const
{
    // Add the systems that need to be processed in our game
    registry->AddSystem<MovementSystem>();
    registry->AddSystem<RenderSystem>();
    registry->AddSystem<AnimationSystem>();
    registry->AddSystem<CollisionSystem>();
    registry->AddSystem<RenderColliderSystem>();
    registry->AddSystem<DamageSystem>();
//    registry->AddSystem<KeyboardControlSystem>();
    registry->AddSystem<CameraMovementSystem>();
    registry->AddSystem<ProjectileEmitSystem>();
    registry->AddSystem<ProjectileLifecycleSystem>();
    registry->AddSystem<RenderTextSystem>();

    registry->AddSystem<RenderColliderSystem>();
    registry->AddSystem<PlayerControlSystem>();
    registry->AddSystem<RenderImGuiSystem>();
//    registry->AddSystem<StateMachineSystem>();
    registry->AddSystem<RenderRaycastSystem>();
}

/**
  * Initialise the assetStore with pointers to png.
  *
 */
void Game::SetupAssets() const
{
    // Adding assets to the asset store
    assetStore->AddTexture(gameRenderer, "hud", "../Game/assets/images/hud2.png");
    assetStore->AddFont("charriot-font", "../Game/assets/fonts/zx-spectrum.ttf", 24);
    assetStore->AddTexture(gameRenderer, "tilemap-image", mapImagePath);
    assetStore->AddTexture(gameRenderer, "tank-image", "../Game/assets/images/tank-panther-right.png");
    assetStore->AddTexture(gameRenderer, "truck-image", "../Game/assets/images/truck-ford-right.png");
    assetStore->AddTexture(gameRenderer, "chopper-image", "../Game/assets/images/chopper.png");
    assetStore->AddTexture(gameRenderer, "player-idle-image", "../Game/assets/sprites/CharacterIdle.png");
    assetStore->AddTexture(gameRenderer, "bullet-image", "../Game/assets/images/bullet.png");
}

/**
* Initialise the player object with components.
 */
void Game::SetupObjects() const
{
    Entity player = registry->CreateEntity();
    player.Tag("player");
    player.AddComponent<TransformComponent>(glm::vec2(256, 256), glm::vec2(2.0, 2.0), 0.0);
    player.AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0));
    player.AddComponent<SpriteComponent>("player-idle-image", 32, 32, 1, false, false);
    player.AddComponent<AnimationComponent>(6, 8, true);
//    player.AddComponent<CameraFollowComponent>();
    player.AddComponent<BoxColliderComponent>(32, 32);
    player.AddComponent<PlayerControllerComponent>(glm::vec2(0, -80.0), glm::vec2(80.0, 0), glm::vec2(0, 80.0), glm::vec2(-80.0, 0));
    player.AddComponent<HealthComponent>(100);
    player.AddComponent<RaycastComponent>(glm::vec2(256, 256));
//    player.AddComponent<StateMachineComponent>("idle");
//    player.AddComponent<ProjectileEmitterComponent>(glm::vec2(150, 0), 1000, 1000, 10, false);

//    Entity tank = registry->CreateEntity();
//    tank.AddComponent<TransformComponent>(glm::vec2(0.0, 100.0), glm::vec2(2.0, 2.0), 0.0);
//    tank.AddComponent<RigidBodyComponent>(glm::vec2(20.0, 0.0));
//    tank.AddComponent<SpriteComponent>("tank-image", 32, 32, 1, false, 0, 0);
//    tank.AddComponent<BoxColliderComponent>(32-10, 32-10, glm::vec2(10,10));
//    tank.AddComponent<ProjectileEmitterComponent>(glm::vec2(150, 0), 1000, 1000, 10, false);

//    Entity label = registry->CreateEntity();
//    SDL_Color red = {255,0,0};
//    label.AddComponent<TextLabelComponent>(glm::vec2(200, 200), "This is a label", "charriot-font", red, true);

}


/**
 * Initial setup of the SDL and true type fonts
 * @return
 */
int Game::SetupSDL()
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

    Logger::Log("SDL is ready to go!");

    return true;
}


/**
 * Setup game SDL window, renderer and camera
 *
 * @return -1 for errors
 */
int Game::SetupRgeSDL()
{
    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);

    // Create window with SDL_Renderer graphics context
    auto windowFlags = (SDL_WindowFlags) (SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN | SDL_WINDOW_ALWAYS_ON_TOP);
    Game::rgeWindow = SDL_CreateWindow(
            "Retro Game Engine v1",
            displayMode.w / 2,
            0,
            displayMode.w / 2,
            displayMode.h,
            windowFlags
    );

    if (!rgeWindow)
    {
        Logger::Error("Window init failed");
        SDL_Quit();
        return false;
    }

//    rgeSurface = SDL_GetWindowSurface(rgeWindow);
//
//    if(!rgeSurface)
//    {
//        std::cout << "Failed to get the surface from the window\n";
//        return -1;
//    }
//
//    SDL_UpdateWindowSurface(rgeWindow);

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
 * Setup game SDL window, renderer and camera
 *
 * @return -1 for errors
 */
int Game::SetupGameSDL()
{
    // Create window with SDL_Renderer graphics context
    auto windowFlags = (SDL_WindowFlags) (SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN | SDL_WINDOW_ALWAYS_ON_TOP);
    Game::gameWindow = SDL_CreateWindow(
            "Game",
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

//    gameSurface = SDL_GetWindowSurface(gameWindow);
//
//    if(!gameSurface)
//    {
//        std::cout << "Failed to get the surface from the window\n";
//        return -1;
//    }
//
//    SDL_UpdateWindowSurface(gameWindow);

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
 * Initial setup of ImGui
 */
void Game::SetupImGui() const
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
//    ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForSDLRenderer(rgeWindow, rgeRenderer);
    ImGui_ImplSDLRenderer2_Init(rgeRenderer);

}


/**
 * Poll events:
 *
 * window quit
 * keyboard
 */
void Game::ProcessInput()
{
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent))
    {
        // ImGui
        ImGui_ImplSDL2_ProcessEvent(&sdlEvent);
        ImGuiIO io = ImGui::GetIO();
        int mouseX;
        int mouseY;
        const int buttons = SDL_GetMouseState(&mouseX, &mouseY);
        io.MousePos = ImVec2(mouseX, mouseY);
        io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
        io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);

        if (sdlEvent.type == SDL_KEYUP)
        {
            eventBus->EmitEvent<KeyReleasedEvent>(sdlEvent.key.keysym.sym);
        }

        // Core sdl events.
        switch (sdlEvent.type)
        {
            case SDL_QUIT:
                isRunning = false;
                break;

            case SDL_KEYDOWN:
                if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) { isRunning = false; }
                if (sdlEvent.key.keysym.sym == SDLK_c) { isCollider = !isCollider; }
                if (sdlEvent.key.keysym.sym == SDLK_r) { isRayCast = !isRayCast; }
                eventBus->EmitEvent<KeyPressedEvent>(sdlEvent.key.keysym.sym);
                break;

            case SDL_WINDOWEVENT:

                switch (sdlEvent.window.event) {

                    case SDL_WINDOWEVENT_CLOSE:   // exit game
                        isRunning = false;
                        break;

                    default:
                        break;
                }
                break;
        }
    };
};


/**
 * UpdateSystems
 */
void Game::UpdateSystems()
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

    registry->GetSystem<MovementSystem>().Update(deltaTime);
    registry->GetSystem<AnimationSystem>().Update();
    registry->GetSystem<CollisionSystem>().Update(eventBus);
    registry->GetSystem<CameraMovementSystem>().Update(gameCamera);
    registry->GetSystem<ProjectileEmitSystem>().Update(registry);
    registry->GetSystem<ProjectileLifecycleSystem>().Update();

}


/**
 * Call render on all objects
 */
void Game::Render()
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
    SDL_Texture* hud = assetStore->GetTexture("hud");
    SDL_Rect source;
    source.x = 0;
    source.y = 0;
    source.w = 640;
    source.h = 64;

    SDL_Rect destination;
    destination.x = 0;
    destination.y = 480-64;
    destination.w = 640;
    destination.h = 64;

    SDL_RenderCopy(gameRenderer, hud, &source, &destination);
    // Debug Line: Player is show if called.
    SDL_RenderPresent(gameRenderer);

//    RenderTree();


    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), rgeRenderer);
    SDL_RenderPresent(rgeRenderer);

}


/**
 * Load the tmx map files and iterate over.
 *
 * @return
 */
int Game::SetupTMX()
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
                        tile.Tag("tile");

                        tile.AddComponent<TransformComponent>(glm::vec2(x * tileWidth, y * tileHeight), glm::vec2(1, 1), 0.0);
                        tile.AddComponent<SpriteComponent>("tilemap-image", tileWidth, tileHeight, 0, true, false, srcRectX, srcRectY);
                        index++;
                    }
                }
            }
        }

        const auto& tilesets = map.getTilesets();
        for(const auto& tileset : tilesets)
        {
            Logger::Log(tileset.getImagePath());
            //read out tile set properties, load textures etc...
        }
    }

    return 0;
}


/**
 * Setup the game data
 */
void Game::Setup()
{
    SetupSDL();
    SetupRgeSDL();
    SetupGameSDL();
    SetUpRegistry();
    SetupAssets();
    SetupImGui();
    SetupObjects();
    SetupTMX();
}


/**
 * Main loop
 */
void Game::Run()
{
    // Set game running on
    isRunning = true;

    while (isRunning)
    {
        ProcessInput();
        UpdateSystems();
        Render();
    }
}


/**
 * Destroy
 */
void Game::Destroy() const
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

