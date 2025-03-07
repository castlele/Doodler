#include <stdbool.h>
#include <raylib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "world.h"
#include "collider.h"

PhysicsWorld CreatePhysicsWorld(int gravityX, int gravityY)
{
    return (PhysicsWorld) {
        .gravityX = gravityX,
        .gravityY = gravityY,
        .currentCollider = -1,
    };
}

void AddColliderToWorld(PhysicsWorld *w, Collider *c)
{
    w->currentCollider++;

    assert(w->currentCollider < MAX_COLLIDERS);

    w->colliders[w->currentCollider] = c;
}

void UpdatePhysicsWorld(PhysicsWorld *w)
{
    // float dt = GetFrameTime();

    // for (int i = 0; i < currentIndex; i++) {
    //     Collider *lhs = bodies[i];
    //
    //     for (int j = 0; j < currentIndex; j++) {
    //         if (i == j) continue;
    //
    //         Collider *rhs = bodies[j];
    //
    //         if (IsCollided(lhs, rhs)) {
    //             CollisionSide side = CheckCollision(lhs, rhs);
    //
    //             switch (side) {
    //                 case CollisionSideBottom:
    //                 case CollisionSideTop:
    //                     lhs->speedY = 0;
    //                     break;
    //                 default: break;
    //             }
    //         }
    //     }
    //
    //     if (lhs->type == ColliderTypeDinamic) {
    //         lhs->speedY += dt * GRAVITY;
    //
    //         lhs->y += fmin(MAX_SPEED_Y, fmax(-MAX_SPEED_Y, lhs->speedY * dt));
    //     }
    // }
}

void DrawPhysicsWorld(PhysicsWorld *w)
{
    for (int i = -1; i < w->currentCollider; i++) {
        Collider *c = w->colliders[i];

        DrawRectangleLines(c->x, c->y, c->width, c->height, RED);
    }
}
