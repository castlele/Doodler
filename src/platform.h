#ifndef PLATFORM_H_
#define PLATFORM_H_

#include <raylib.h>
#include <stdbool.h>
#include "physics/collider.h"

typedef struct Platform
{
    int x;
    int y;
    bool hidden;
    Collider *collider;
} Platform;

// TODO: Both this methods is kinda useless and have to be removed
int GetPlatformWidth();
int GetPlatformHeight();
Rectangle GetPlatformRect(Platform *p);

Platform *CreatePlatform(int x, int y, bool hidden);
void UpdatePlatform(Platform *p);
void DrawPlatform(Platform *p);

#endif
