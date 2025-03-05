#include <raylib.h>

#include "platform.h"

#define PLATFORM_W 100
#define PLATFORM_H 20

int GetPlatformWidth()
{
    return PLATFORM_W;
}

int GetPlatformHeight()
{
    return PLATFORM_H;
}

Rectangle GetPlatformRect(Platform *p)
{
    return (Rectangle) {
        .x = p->x,
        .y = p->y,
        .width = GetPlatformWidth(),
        .height = GetPlatformHeight(),
    };
}

Platform CreatePlatform(int x, int y)
{
    return (Platform) {
        .x = x,
        .y = y,
    };
}

void UpdatePlatform(Platform *p)
{
    p->x = p->collider->x;
    p->y = p->collider->y;
}

void DrawPlatform(Platform *p)
{
    DrawRectangle(p->x, p->y, GetPlatformWidth(), GetPlatformHeight(), BROWN);
}

