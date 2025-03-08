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

void UpdatePlayer(Player *p)
{
    p->x = p->collider->x;
    p->y = p->collider->y;
}

void DrawPlayer(Player *p)
{
    DrawRectangle(p->x, p->y, PLAYER_W, PLAYER_H, GREEN);
}
