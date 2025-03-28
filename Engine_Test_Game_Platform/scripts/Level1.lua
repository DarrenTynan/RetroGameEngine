-- Define a table with the start values of the first level
Level = {
    ----------------------------------------------------
    -- Table to define the list of assets
    ----------------------------------------------------
    assets = {
        [0] =
        { type = "font",    id = "arial-font",                  file = "../Engine_Test_Game_Platform/assets/fonts/arial.ttf", font_size = 18 },
        { type = "texture", id = "tilemap-image",               file = "../Engine_Test_Game_Platform/assets/tile-maps/EngineTestLevel/EngineTestLevel.png" },
        { type = "texture", id = "player-idle-image",           file = "../Engine_Test_Game_Platform/assets/sprites/CharacterIdle.png" },
        { type = "texture", id = "tank-image",                  file = "../Engine_Test_Game_Platform/assets/images/tank-panther-right.png" },
        { type = "texture", id = "truck-image",                 file = "../Engine_Test_Game_Platform/assets/images/truck-ford-right.png" },
        { type = "texture", id = "chopper-image",               file = "../Engine_Test_Game_Platform/assets/images/chopper.png" },
        { type = "texture", id = "bullet-image",                file = "../Engine_Test_Game_Platform/assets/images/bullet.png" },
    },

    ----------------------------------------------------
    -- table to define the map config variables
    ----------------------------------------------------
    tilemap = {
       map_file = "../Engine_Test_Game_Platform/assets/tile-maps/EngineTestLevel/EngineTestLevel.tmx",
--        texture_asset_id = tilemap-image,
       tile_count_x = 40,
       tile_count_y = 22,
       tile_size = 32,
       scale = 1.0
    },

    ----------------------------------------------------
    -- table to define entities and their components
    ----------------------------------------------------
    entities = {
        [0] =
        {
            -- Player
            tag = "player",
            components = {
                transform = {
                    start_position = { x = 32*10, y = 32*7 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                rigidbody = {
                    deltaXY = { x = 0.0, y = 0.0 },
                    maxDeltaXY = { x = 3.0, y = 3.0 },
                    acceleration = 0.5,
                    boost = 4.0,
                    gravity = 0.12, -- 0.3
                    friction = 0.85,
                },
                sprite = {
                    idle = {
                        texture_asset_id = "player-idle-image",
                        width = 32,
                        height = 32,
                        z_index = 4,
                        fixed = false,
                        src_rect_x = 0,
                        src_rect_y = 0,
                        animation = {
                            num_frames = 6,
                            speed_rate = 8 -- fps
                        },
                    }
                },
                --animation = {
                --    num_frames = 6,
                --    speed_rate = 8 -- fps
                --},
                box_collider = {
                    width = 32,
                    height = 32,
                    position = {x = 0, y = 0},
                    has_ray_cast = true
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    projectile_velocity = { x = 200, y = 200 },
                    projectile_duration = 10, -- seconds
                    repeat_frequency = 0, -- seconds
                    hit_percentage_damage = 10,
                    friendly = true
                },
                camera_follow = {
                    follow = true
                },
                text_label = {}
            }
        },

        on_update_script =
        {
            --[0] =
            --function(entity, delta_time, ellapsed_time)
            --    -- this function makes the fighter jet move up and down the map shooting projectiles
            --    local current_position_x, current_position_y = get_position(entity)
            --    local current_velocity_x, current_velocity_y = get_velocity(entity)
            --
            --    -- if it reaches the top or the bottom of the map
            --    if current_position_y < 10 or current_position_y > map_height - 32 then
            --        set_velocity(entity, 0, current_velocity_y * -1); -- flip the entity y-deltaXY
            --    else
            --        set_velocity(entity, 0, current_velocity_y); -- do not flip y-deltaXY
            --    end
            --
            --    -- set the transform rotation to match going up or down
            --    if (current_velocity_y < 0) then
            --        set_rotation(entity, 0) -- point up
            --        set_projectile_velocity(entity, 0, -200) -- shoot projectiles up
            --    else
            --        set_rotation(entity, 180) -- point down
            --        set_projectile_velocity(entity, 0, 200) -- shoot projectiles down
            --    end
            --end
        }
    }
}

-- Define some useful global variables
debug_text = "DEBUG"
-- map_width = Level.tilemap.num_cols * Level.tilemap.tile_size * Level.tilemap.scale
-- map_height = Level.tilemap.num_rows * Level.tilemap.tile_size * Level.tilemap.scale
