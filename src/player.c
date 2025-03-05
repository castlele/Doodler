#include <raylib.h>
#include <stdbool.h>

#include "player.h"
#include "config.h"
#include "platform.h"

#define PLAYER_W 50
#define PLAYER_H 50

void ApplyGravity(Player *p);
void MovePlayer(Player *p);

Rectangle GetPlayerRect(Player *p)
{
    return (Rectangle) {
        .x = p->x,
        .y = p->y,
        .width = PLAYER_W,
        .height = PLAYER_H,
    };
}

Player CreatePlayer(int x, int y)
{
    return (Player) {
        .x = x,
        .y = y,
    };
}

void UpdatePlayer(Player *p)
{
    p->x = p->collider->x;
    p->y = p->collider->y;
}

void DrawPlayer(Player *p)
{
    DrawRectangle(p->x, p->y, PLAYER_W, PLAYER_H, GREEN);
}

// TODO: Move to physics module
void CheckPlayerCollisionWithPlatform(Player *p, Platform *plat)
{
    bool collide = CheckCollisionRecs(GetPlayerRect(p), GetPlatformRect(plat));

    // TODO: Check where player and plat are collided

    if (collide) {
        p->y = plat->y - PLAYER_H;
    }
}

// Private Methods Declarations

void ApplyGravity(Player *p)
{
    p->y += GetGravity() * GetFrameTime();
}

void MovePlayer(Player *p)
{
    // TODO: Move velocity to constant or configuration
    int velocity = 150;
    float dt = GetFrameTime();

    // TODO: Add keys to the config and make them editable from the game :)
    if (IsKeyDown(KEY_LEFT)) {
        p->x -= velocity * dt;
    }

    if (IsKeyDown(KEY_RIGHT)) {
        p->x += velocity * dt;
    }

    if (IsKeyDown(KEY_SPACE)) {
        p->y -= velocity * dt;
    }
}
