#include <raylib.h>

#include "platforms.h"
#include "platform.h"

#define STEPS 10

void SetPlatfromPosition(Platform *p, int minY, int maxY);

PlatformsFactory CreatePlatformFactory()
{
    PlatformsFactory f = {};

    for (int i = 0; i < MAX_PLATFORMS; i++) {
        Platform *p = CreatePlatform(0, 0, true);

        f.platforms[i] = p;
    }

    return f;
}

void SetPlatformColliders(PlatformsFactory *f, PhysicsWorld *w)
{

    for (int i = 0; i < MAX_PLATFORMS; i++) {
        Platform *p = f->platforms[i];

        if (!p) continue;

        p->collider = CreateCollider(
            p->x,
            p->y,
            GetPlatformWidth(),
            GetPlatformHeight(),
            ColliderTypeStatic,
            0
        );
        SetColliderMask(p->collider, "platform");
        AddColliderToWorld(w, p->collider);
    }

}

void UpdatePlatforms(PlatformsFactory *f)
{
    for (int i = 0; i < MAX_PLATFORMS; i++) {
        Platform *p = f->platforms[i];

        p->collider->active = !p->hidden;

        UpdatePlatform(p);
    }
}

void DrawPlatforms(PlatformsFactory *f)
{
    for (int i = 0; i < MAX_PLATFORMS; i++) {
        DrawPlatform(f->platforms[i]);
    }
}

void ResetPlatforms(PlatformsFactory *f)
{
    int h = GetScreenHeight();
    int stepH = h / STEPS;
    int platformsPerStep = MAX_PLATFORMS / STEPS;

    for (int step = 0; step < MAX_PLATFORMS; step += platformsPerStep) {
        int minY = h - stepH * step;
        int maxY = h - (stepH * step + stepH);

        for (int i = 0; i < platformsPerStep; i++) {
            Platform *p = f->platforms[i + step];
            p->hidden = false;

            SetPlatfromPosition(p, minY, maxY);
        }
    }
}

// Private Methods Definitions

void SetPlatfromPosition(Platform *p, int minY, int maxY)
{
    if (p->collider) {
        p->collider->position.x = GetRandomValue(0, GetScreenWidth() - GetPlatformWidth());
        p->collider->position.y = GetRandomValue(minY, maxY);
    } else {
        p->x = GetRandomValue(0, GetScreenWidth() - GetPlatformWidth());
        p->y = GetRandomValue(minY, maxY);
    }
}
