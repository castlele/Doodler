#ifndef PLAYER_H_
#define PLAYER_H_

#include <raylib.h>

#include "platform.h"
#include "physics/collider.h"

typedef struct Player
{
    int x;
    int y;
    Collider *collider;
} Player;

Rectangle GetPlayerRect(Player *p);

Player CreatePlayer(int x, int y);

void UpdatePlayer(Player *p, float dt);
void DrawPlayer(Player *p);

void CheckPlayerCollisionWithPlatform(Player *p, Platform *plat);

#endif
