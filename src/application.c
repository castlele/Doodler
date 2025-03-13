#include <raylib.h>
#include <stdio.h>

#include "application.h"
#include "config.h"
#include "physics/world.h"
#include "platforms.h"
#include "player.h"
#include "score.h"

typedef struct App
{
    PhysicsWorld world;
    PlatformsFactory platformsFactory;
    Player player;
} App;

App _app;

void Update(float dt);
void Draw();

void ApplyConfig();
void ListenEvents();

void InitApplication()
{
    _app = (App) {
        .player = CreatePlayer(DEFAULT_SCREEN_W / 2, DEFAULT_SCREEN_H / 2),
        .world = CreatePhysicsWorld(GRAVITY_X, GRAVITY_Y),
        .platformsFactory = CreatePlatformFactory(),
    };

    SetPlatformColliders(&_app.platformsFactory, &_app.world);
    AddColliderToWorld(&_app.world, _app.player.collider);
}

void RunApplication()
{
    ApplyConfig();

    // TODO: Make window resizable
    //       https://www.reddit.com/r/raylib/comments/a19a67/resizable_window_questions/
    InitWindow(DEFAULT_SCREEN_W, DEFAULT_SCREEN_H, APP_NAME);

    ResetPlatforms(&_app.platformsFactory);

    float dt;

    while (!WindowShouldClose()) {
        dt = GetFrameTime();

        Update(dt);

        ListenEvents();

        BeginDrawing();
            ClearBackground(WHITE);

            Draw();
        EndDrawing();
    }

    CloseWindow();
}

// Private methods declarations

void Update(float dt)
{
    UpdatePhysicsWorld(&_app.world, dt);
    UpdatePlatforms(&_app.platformsFactory);
    UpdatePlayer(&_app.player, dt);
    UpdateScore(_app.player.y, _app.player.width);
}

void ListenEvents()
{
    if (IsKeyPressed(KEY_R)) {
        ResetPlayerPos(&_app.player);
        ResetPlatforms(&_app.platformsFactory);
    }
}

void Draw()
{
    DrawPlatforms(&_app.platformsFactory);
    DrawPlayer(&_app.player);
    DrawScore();
    DrawPhysicsWorld(&_app.world);
}

void ApplyConfig()
{
    // TODO: Make this value configurable
    // FIX: Why setting fps shouldn't be used?
    // https://bedroomcoders.co.uk/posts/218
    SetTargetFPS(60);
}
