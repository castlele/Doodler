#ifndef PLATFORMS_H_
#define PLATFORMS_H_

#include "physics/world.h"
#include "platform.h"

#define MAX_PLATFORMS 10

typedef struct PlatformsFactory
{
    Platform *platforms[MAX_PLATFORMS];
} PlatformsFactory;

PlatformsFactory CreatePlatformFactory();
void SetPlatformColliders(PlatformsFactory *f, PhysicsWorld *w);

void UpdatePlatforms(PlatformsFactory *f);
void DrawPlatforms(PlatformsFactory *f);

void ResetPlatforms(PlatformsFactory *f);

#endif
