#include <raylib.h>

#include "platform.h"
#include "player.h"

#define SCREEN_W 800
#define SCREEN_H 600

void ApplyConfig();

int main()
{
    ApplyConfig();

    int platformW = GetPlatformWidth();
    int platformH = GetPlatformHeight();
    Platform platform = CreatePlatform(
        (SCREEN_W - platformW) / 2,
        (SCREEN_H - platformH) / 2
    );

    Player player = CreatePlayer(platform.x, platform.y - 100);

    // TODO: Make window resizable
    //       https://www.reddit.com/r/raylib/comments/a19a67/resizable_window_questions/
    InitWindow(SCREEN_W, SCREEN_H, "Doodler");

    while (!WindowShouldClose()) {
        UpdatePlatform(&platform);
        UpdatePlayer(&player);

        CheckPlayerCollisionWithPlatform(&player, &platform);

        BeginDrawing();
            ClearBackground(WHITE);

            DrawPlatform(&platform);
            DrawPlayer(&player);
        EndDrawing();
    }

    return 0;
}

// Private methods declarations

void ApplyConfig()
{
    // TODO: Make this value configurable
    SetTargetFPS(60);
}
