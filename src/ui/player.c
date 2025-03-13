#include <raylib.h>
#include <stdbool.h>

#include "player.h"
#include "physics/collider.h"

#define PLAYER_W 50
#define PLAYER_H 50

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
    Player p = {
        .x = x,
        .y = y,
        .width = PLAYER_W,
        .height = PLAYER_H,
    };

    p.collider = CreateCollider(
        p.x,
        p.y,
        p.width,
        p.height,
        ColliderTypeDynamic,
        50
    );

    return p;
}

void UpdatePlayer(Player *p, float dt)
{
    p->x = p->collider->position.x;
    p->y = p->collider->position.y;

    if (IsKeyDown(KEY_LEFT)) {
        p->collider->velocity.x -= 1000 * dt;
    } else if (IsKeyDown(KEY_RIGHT)) {
        p->collider->velocity.x += 1000 * dt;
    } else {
        p->collider->velocity.x = 0;
    }

    int halfW = PLAYER_W / 2;

    if (p->x + halfW < 0) {
        p->collider->position.x = p->x + GetScreenWidth();
    } else if (p->x + halfW > GetScreenWidth()) {
        p->collider->position.x = p->x - GetScreenWidth();
    }
}

void DrawPlayer(Player *p)
{
    DrawRectangle(p->x, p->y, PLAYER_W, PLAYER_H, GREEN);
}

void ResetPlayerPos(Player *p)
{
    int x = GetScreenWidth() / 2;
    int y = GetScreenHeight() / 2;

    p->collider->position.x = x;
    p->collider->position.y = y;
}
