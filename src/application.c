#include <math.h>
#include <raylib.h>
#include <stdio.h>

#include "application.h"
#include "physics/world.h"
#include "physics/collider.h"
#include "platforms.h"
#include "player.h"

typedef struct App
{
    PhysicsWorld world;
    PlatformsFactory platformsFactory;
    Player player;
    int level;
    int score;
} App;

App _app;

void Update(float dt);
void Draw();

void ApplyConfig();
void ListenEvents();
void UpdateLevel();
void UpdateScore();
void DrawScore();

void InitApplication()
{
    _app = (App) {
        .player = CreatePlayer(400 / 2, 600 / 2),
        .world = CreatePhysicsWorld(0, 800),
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
    InitWindow(400, 600, "Doodler");

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
    UpdateLevel();
    UpdateScore();
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

void ListenEvents()
{
    if (IsKeyPressed(KEY_R)) {
        _app.level = 1;
        _app.score = 0;
        ResetPlayerPos(&_app.player);
        ResetPlatforms(&_app.platformsFactory);
    }
}

void UpdateLevel()
{
    // TODO: Refactor?
    if (_app.player.y + 25 < 0) {
        _app.player.collider->position.y = GetScreenHeight() - 25;
        _app.player.collider->velocity.y -= 50;
        _app.level++;
        ResetPlatforms(&_app.platformsFactory);
    } else if (_app.player.y + 25 > GetScreenHeight()) {
        _app.level = 1;
        _app.score = 0;
        ResetPlayerPos(&_app.player);
        ResetPlatforms(&_app.platformsFactory);
    }
}

void UpdateScore()
{
    int h = GetScreenHeight();
    _app.score = fmax((h - _app.player.y) * _app.level, _app.score);
}

void DrawScore()
{
    char scoreMessage[64];
    sprintf(scoreMessage, "SCORE: %d", _app.score);

    DrawText(scoreMessage, GetScreenWidth() / 2, 0, 32, BLACK);
}
