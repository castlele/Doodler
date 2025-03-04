#ifndef PLAYER_H_
#define PLAYER_H_

#include "platform.h"

typedef struct Player
{
    int x;
    int y;
} Player;

Player CreatePlayer(int x, int y);

void UpdatePlayer(Player *p);
void DrawPlayer(Player *p);

void CheckPlayerCollisionWithPlatform(Player *p, Platform *plat);

#endif
