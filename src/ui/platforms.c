#include <raylib.h>

#include "platforms.h"
#include "platform.h"

#define MIN_PLATFORMS_AMOUNT 2
#define MAX_PLATFORMS_AMOUNT (MAX_PLATFORMS / 2)

void SetPlatfromPosition(Platform *p, int minY, int maxY);

PlatformsFactory CreatePlatformFactory()
{
    PlatformsFactory f = {
        .currentBottom = GetRandomValue(MIN_PLATFORMS_AMOUNT, MAX_PLATFORMS_AMOUNT),
        .currentTop = GetRandomValue(MIN_PLATFORMS_AMOUNT, MAX_PLATFORMS_AMOUNT),
    };

    int platformsAmount = f.currentTop + f.currentBottom;
    int h = GetScreenHeight();

    for (int i = 0; i < MAX_PLATFORMS; i++) {
        Platform *p = CreatePlatform(0, 0, true);

        if (i < platformsAmount) {
            p->hidden = false;

            if (i <= platformsAmount / 2) {
                SetPlatfromPosition(p, h - GetPlatformHeight(), h / 2);
            } else if (i > platformsAmount / 2) {
                SetPlatfromPosition(p, h / 2, 0);
            }
        }

        f.platforms[i] = p;
    }

    return f;
}

void SetPlatformColliders(PlatformsFactory *f, PhysicsWorld *w)
{

    for (int i = 0; i < MAX_PLATFORMS; i++) {
        Platform *p = f->platforms[i];

        if (!p) break;

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
    f->currentBottom = GetRandomValue(MIN_PLATFORMS_AMOUNT, MAX_PLATFORMS_AMOUNT);
    f->currentTop = GetRandomValue(MIN_PLATFORMS_AMOUNT, MAX_PLATFORMS_AMOUNT);

    int platformsAmount = f->currentTop + f->currentBottom;
    int h = GetScreenHeight();

    for (int i = 0; i < MAX_PLATFORMS; i++) {
        Platform *p = f->platforms[i];

        if (i < platformsAmount) {
            p->hidden = false;

            if (i <= platformsAmount / 2) {
                SetPlatfromPosition(p, h - GetPlatformHeight(), h / 2);
            } else if (i > platformsAmount / 2) {
                SetPlatfromPosition(p, h / 2, 0);
            }
        } else {
            p->hidden = true;
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
