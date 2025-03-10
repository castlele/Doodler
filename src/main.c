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

    float dt;
    PhysicsWorld world = CreatePhysicsWorld(0, 800);

    int platformW = GetPlatformWidth();
    int platformH = GetPlatformHeight();
    Platform platform = CreatePlatform(
        (SCREEN_W - platformW) / 2,
        (SCREEN_H - platformH) / 2
    );

    Player player = CreatePlayer(platform.x, platform.y - 100);
    Rectangle pr = GetPlayerRect(&player);
    Rectangle platr = GetPlatformRect(&platform);

    player.collider = CreateCollider(
        pr.x,
        pr.y,
        pr.width,
        pr.height,
        ColliderTypeDinamic,
        50
    );
    SetColliderMask(player.collider, "player");
    platform.collider = CreateCollider(
        platr.x,
        platr.y,
        platr.width,
        platr.height,
        ColliderTypeStatic,
        0
    );
    SetColliderMask(platform.collider, "platform");

    AddColliderToWorld(&world, player.collider);
    AddColliderToWorld(&world, platform.collider);

    // ObserveCollision("player", "platform", PlayerJump);

    // TODO: Make window resizable
    //       https://www.reddit.com/r/raylib/comments/a19a67/resizable_window_questions/
    InitWindow(SCREEN_W, SCREEN_H, "Doodler");

    while (!WindowShouldClose()) {
        dt = GetFrameTime();

        UpdatePhysicsWorld(&world, dt);
        UpdatePlatform(&platform);
        UpdatePlayer(&player);

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
    // FIX: Why setting fps shouldn't be used?
    // https://bedroomcoders.co.uk/posts/218
    SetTargetFPS(60);
}
