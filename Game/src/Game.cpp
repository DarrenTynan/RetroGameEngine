//
// Created by Darren Tynan on 17/11/2024.
//

#include "../include/Game.h"

#if !SDL_VERSION_ATLEAST(2,0,17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

const auto MAP_PATH = "../Game/assets/tilemaps/Level_01.tmx";
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

void Game::RenderTree()
{
    surface = IMG_Load("../Game/assets/images/tree.png");

    texture = SDL_CreateTextureFromSurface(renderer, surface);
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
//    registry->AddSystem<RenderImGuiSystem>();
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
    assetStore->AddTexture(renderer, "hud", "../Game/assets/images/hud2.png");
    assetStore->AddFont("charriot-font", "../Game/assets/fonts/charriot.ttf", 24);
    assetStore->AddTexture(renderer, "tilemap-image", mapImagePath);
    assetStore->AddTexture(renderer, "tank-image", "../Game/assets/images/tank-panther-right.png");
    assetStore->AddTexture(renderer, "truck-image", "../Game/assets/images/truck-ford-right.png");
    assetStore->AddTexture(renderer, "chopper-image", "../Game/assets/images/chopper.png");
    assetStore->AddTexture(renderer, "player-idle-image", "../Game/assets/sprites/CharacterIdle.png");
    assetStore->AddTexture(renderer, "bullet-image", "../Game/assets/images/bullet.png");
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
 * SetupSDL SDL, DisplayMode, Window, Camera, ImGui
 *
 * @return -1 for errors
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

    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    windowWidth = SCREEN_WIDTH;
    windowHeight = SCREEN_HEIGHT;
//    windowWidth = displayMode.w;
//    windowHeight = displayMode.h;

    // Create window with SDL_Renderer graphics context
    auto windowFlags = (SDL_WindowFlags) (SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
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
        SDL_Quit();
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer)
    {
        Logger::Error("Window renderer init failed");
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        return false;
    }

    Logger::Log("SDL is ready to go!");

    // SetupSDL the camera view with the entire screen area
    camera = {0, 0, windowWidth, windowHeight};

    return true;
}

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
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);

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
                if (sdlEvent.key.keysym.sym == SDLK_d) { isDebug = !isDebug; }
                if (sdlEvent.key.keysym.sym == SDLK_g) { isImGui = !isImGui; }
                eventBus->EmitEvent<KeyPressedEvent>(sdlEvent.key.keysym.sym);
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
    registry->GetSystem<CameraMovementSystem>().Update(camera);
    registry->GetSystem<ProjectileEmitSystem>().Update(registry);
    registry->GetSystem<ProjectileLifecycleSystem>().Update();

};


void Game::Destroy() const
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
    bool show_demo_window = true;
    bool show_another_window = false;

    // Poll and handle events (inputs, window resize, etc.)
    // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui_basic wants to use your inputs.
    // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
    // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
    // Generally you may always pass all inputs to dear imgui_basic, and hide them from your application based on those two flags.
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL2_ProcessEvent(&event);
        if (event.type == SDL_QUIT) isRunning = false;
        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
            isRunning = false;
    }

    if (SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED) { SDL_Delay(10); }

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
//        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
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
//    SDL_SetRenderDrawColor(renderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
//    SDL_RenderClear(renderer);
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
    SDL_RenderPresent(renderer);

}


void Game::Render()
{
    SDL_SetRenderDrawColor(renderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
    SDL_RenderClear(renderer);

    // Invoke all the systems that need to render
    registry->GetSystem<RenderSystem>().Update(renderer, assetStore, camera);
    registry->GetSystem<RenderTextSystem>().Update(renderer, assetStore, camera);

    if (isDebug) {
        registry->GetSystem<RenderColliderSystem>().Update(renderer, camera);
        auto player = registry->GetEntityByTag("player");
        registry->GetSystem<RenderRaycastSystem>().Update(renderer, player);
    }

    if (isImGui) {
        RenderImGui();
//        registry->GetSystem<RenderImGuiSystem>().Update(registry, camera);
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

    SDL_RenderCopy(renderer, hud, &source, &destination);

    // Causes flicker but if removed then no map displayed.
    SDL_RenderPresent(renderer);

}

/**
 * Load the tmx map files and iterate over.
 *
 * @return
 */
int Game::GetTMX()
{
    map.load(MAP_PATH);

    if(map.load(MAP_PATH))
    {
        const auto& layers = map.getLayers();
        for(const auto& layer : layers)
        {
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

                        tile.AddComponent<TransformComponent>(glm::vec2(x * tileWidth, y * tileHeight), glm::vec2(1, 1), 0.0);
                        tile.AddComponent<SpriteComponent>("tilemap-image", tileWidth, tileHeight, 0, true, false, srcRectX, srcRectY);
//                        tile.AddComponent<BoxColliderComponent>(32,32);
                        index++;
                    }
                }
            }
        }

        const auto& tilesets = map.getTilesets();
        for(const auto& tileset : tilesets)
        {
            //read out tile set properties, load textures etc...
        }
    }

    return 0;
}



/**
 * Main loop
 */
void Game::Run()
{
    SetupSDL();
    SetUpRegistry();
    SetupAssets();
    SetupImGui();
    SetupObjects();
    GetTMX();

    // Set game running on
    isRunning = true;

    while (isRunning)
    {
        ProcessInput();
        UpdateSystems();    // contains the delta time loop
        Render();

//        RenderTree();
//        RenderImGui();
    }
}
