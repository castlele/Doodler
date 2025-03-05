#include <raylib.h>

#include "physics/world.h"
#include "physics/collider.h"
#include "platform.h"
#include "player.h"

#define SCREEN_W 800
#define SCREEN_H 600

void ApplyConfig();

int main()
{
    ApplyConfig();

    PhysicsWorld world = CreatePhysicsWorld(0, 500);

    int platformW = GetPlatformWidth();
    int platformH = GetPlatformHeight();
    Platform platform = CreatePlatform(
        (SCREEN_W - platformW) / 2,
        (SCREEN_H - platformH) / 2
    );

    Player player = CreatePlayer(platform.x, platform.y - 100);
    Rectangle pr = GetPlayerRect(&player);
    Rectangle platr = GetPlatformRect(&platform);

    player.collider = AddCollider((ColliderData){
        .x = pr.x,
        .y = pr.y,
        .width = pr.width,
        .height = pr.height,
        .type = ColliderTypeDinamic,
    });
    platform.collider = AddCollider((ColliderData){
        .x = platr.x,
        .y = platr.y,
        .width = platr.width,
        .height = platr.height,
        .type = ColliderTypeStatic,
    });

    // TODO: Make window resizable
    //       https://www.reddit.com/r/raylib/comments/a19a67/resizable_window_questions/
    InitWindow(SCREEN_W, SCREEN_H, "Doodler");

    while (!WindowShouldClose()) {
        UpdatePhysicsWorld(&world);
        UpdatePlatform(&platform);
        UpdatePlayer(&player);

        // CheckPlayerCollisionWithPlatform(&player, &platform);

        BeginDrawing();
            ClearBackground(WHITE);

            DrawPlatform(&platform);
            DrawPlayer(&player);
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
    SetTargetFPS(60);
}
