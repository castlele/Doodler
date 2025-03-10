#include <raylib.h>
#include <stdbool.h>

#include "player.h"

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
    return (Player) {
        .x = x,
        .y = y,
    };
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
}

void DrawPlayer(Player *p)
{
    DrawRectangle(p->x, p->y, PLAYER_W, PLAYER_H, GREEN);
}
