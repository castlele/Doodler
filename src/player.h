#ifndef PLAYER_H_
#define PLAYER_H_

#include <raylib.h>

#include "platform.h"

typedef struct Player
{
    int x;
    int y;
} Player;

Rectangle GetPlayerRect(Player *p);

Player CreatePlayer(int x, int y);

void UpdatePlayer(Player *p);
void DrawPlayer(Player *p);

void CheckPlayerCollisionWithPlatform(Player *p, Platform *plat);

#endif
