#include <raylib.h>
#include <stdlib.h>

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

Platform *CreatePlatform(int x, int y, bool hidden)
{
    Platform *p = malloc(sizeof(Platform));
    p->x = x;
    p->y = y;
    p->hidden = hidden;

    return p;
}

void UpdatePlatform(Platform *p)
{
    p->x = p->collider->position.x;
    p->y = p->collider->position.y;
}

void DrawPlatform(Platform *p)
{
    if (p->hidden) return;

    DrawRectangle(p->x, p->y, GetPlatformWidth(), GetPlatformHeight(), BROWN);
}

