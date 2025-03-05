#ifndef PLATFORM_H_
#define PLATFORM_H_

#include <raylib.h>
#include "physics/collider.h"

typedef struct Platform
{
    int x;
    int y;
    Collider *collider;
} Platform;

int GetPlatformWidth();
int GetPlatformHeight();
Rectangle GetPlatformRect(Platform *p);

Platform CreatePlatform(int x, int y);
void UpdatePlatform(Platform *p);
void DrawPlatform(Platform *p);

#endif
