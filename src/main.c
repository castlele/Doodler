#include <math.h>
#include <raylib.h>
#include <stdio.h>

#include "physics/world.h"
#include "physics/collider.h"
#include "platforms.h"
#include "player.h"

#define SCREEN_W 400
#define SCREEN_H 600

PlatformsFactory platformsFactory;
Player player;
int level = 1;
int score;

void ApplyConfig();
void ListenEvents();
void UpdateLevel();
void UpdateScore();
void DrawScore();

int main()
{
    ApplyConfig();

    // TODO: Make window resizable
    //       https://www.reddit.com/r/raylib/comments/a19a67/resizable_window_questions/
    InitWindow(SCREEN_W, SCREEN_H, "Doodler");

    float dt;
    PhysicsWorld world = CreatePhysicsWorld(0, 800);
    player = CreatePlayer(SCREEN_W / 2, SCREEN_H / 2);
    platformsFactory = CreatePlatformFactory();

    Rectangle pr = GetPlayerRect(&player);

    player.collider = CreateCollider(
        pr.x,
        pr.y,
        pr.width,
        pr.height,
        ColliderTypeDinamic,
        50
    );

    AddColliderToWorld(&world, player.collider);
    SetPlatformColliders(&platformsFactory, &world);

    while (!WindowShouldClose()) {
        dt = GetFrameTime();

        UpdatePhysicsWorld(&world, dt);
        UpdatePlatforms(&platformsFactory);
        UpdatePlayer(&player, dt);
        UpdateLevel();
        UpdateScore();

        ListenEvents();

        BeginDrawing();
            ClearBackground(WHITE);

            DrawPlatforms(&platformsFactory);
            DrawPlayer(&player);
            DrawScore();
            DrawPhysicsWorld(&world);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

// Private methods declarations

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
        ResetPlayerPos(&player);
        ResetPlatforms(&platformsFactory);
    }
}

void UpdateLevel()
{
    // TODO: Refactor?
    if (player.y + 25 < 0) {
        player.collider->position.y = GetScreenHeight() - 25;
        player.collider->velocity.y -= 50;
        level++;
        ResetPlatforms(&platformsFactory);
    }
}

void UpdateScore()
{
    int h = GetScreenHeight();
    score = fmax((h - player.y) * level, score);
}

void DrawScore()
{
    char scoreMessage[64];
    sprintf(scoreMessage, "SCORE: %d", score);

    DrawText(scoreMessage, GetScreenWidth() / 2, 0, 32, BLACK);
}
