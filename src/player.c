#include <raylib.h>
#include <stdio.h>
#include <stdbool.h>

#include "player.h"
#include "config.h"
#include "platform.h"

#define PLAYER_W 50
#define PLAYER_H 50

void ApplyGravity(Player *p);

Player CreatePlayer(int x, int y)
{
    return (Player) {
        .x = x,
        .y = y,
    };
}

void UpdatePlayer(Player *p)
{
    ApplyGravity(p);
}

void DrawPlayer(Player *p)
{
    DrawRectangle(p->x, p->y, PLAYER_W, PLAYER_H, GREEN);
}

void CheckPlayerCollisionWithPlatform(Player *p, Platform *plat)
{
    bool collide = CheckCollisionRecs(
        // TODO: Getting of this rects should be much easier!
        (Rectangle) {
            .x = p->x,
            .y = p->y,
            .width = PLAYER_W,
            .height = PLAYER_H,
        },
        (Rectangle) {
            .x = plat->x,
            .y = plat->y,
            .width = GetPlatformWidth(),
            .height = GetPlatformHeight(),
        }
    );

    // TODO: Check where player and plat are collided

    if (collide) {
        p->y = plat->y - PLAYER_H;
    }
}

// Private Methods Declarations

void ApplyGravity(Player *p)
{
    p->y += GetGravity() * GetFrameTime();
    printf("Y: %d, EXPECTED: %f\n", p->y, GetGravity() * GetFrameTime());
}
