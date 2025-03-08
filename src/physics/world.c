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
    float dt = GetFrameTime();

    for (int i = 0; i <= w->currentCollider; i++) {
        Collider *lhs = w->colliders[i];

        for (int j = 0; j <= w->currentCollider; j++) {
            if (i == j) continue;

            Collider *rhs = w->colliders[j];
            bool isCollided = CheckCollision(lhs, rhs);

            if (isCollided) {
                CollisionSide side = GetCollisionSide(isCollided, lhs, rhs);

                switch (side) {
                    case CollisionSideBottom:
                    case CollisionSideTop:
                        lhs->speedY = 0;
                        break;
                    case CollisionSideRight:
                    case CollisionSideLeft:
                        rhs->speedX = 0;
                        break;
                }
            }
        }

        if (lhs->type == ColliderTypeDinamic) {
            lhs->speedX += dt * w->gravityX;
            lhs->speedY += dt * w->gravityY;

            // lhs->y += fmin(MAX_SPEED_Y, fmax(-MAX_SPEED_Y, lhs->speedY * dt));
            lhs->x += dt * lhs->speedX;
            lhs->y += dt * lhs->speedY;
        }
    }
}

void DrawPhysicsWorld(PhysicsWorld *w)
{
    for (int i = -1; i < w->currentCollider; i++) {
        Collider *c = w->colliders[i];

        DrawRectangleLines(c->x, c->y, c->width, c->height, RED);
    }
}
