#include <stdbool.h>
#include <raylib.h>
#include <assert.h>

#include "world.h"
#include "collider.h"

void BumpColliders(CollisionSide side, Collider *lhs, Collider *rhs);

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

void UpdatePhysicsWorld(PhysicsWorld *w, float dt)
{
    for (int i = 0; i <= w->currentCollider; i++) {
        Collider *lhs = w->colliders[i];

        if (lhs->type == ColliderTypeStatic) continue;

        for (int j = 0; j <= w->currentCollider; j++) {
            if (i == j) continue;

            Collider *rhs = w->colliders[j];
            bool isCollided = CheckCollision(lhs, rhs);

            if (isCollided) {
                CollisionSide side = GetCollisionSide(isCollided, lhs, rhs);
                BumpColliders(side, lhs, rhs);

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

        lhs->speedX += dt * w->gravityX;
        lhs->speedY += dt * w->gravityY;

        lhs->x += dt * lhs->speedX;
        lhs->y += dt * lhs->speedY;
    }
}

void DrawPhysicsWorld(PhysicsWorld *w)
{
    for (int i = 0; i <= w->currentCollider; i++) {
        Collider *c = w->colliders[i];

        DrawRectangleLines(c->x, c->y, c->width, c->height, RED);
    }
}

// Private declarations

void BumpColliders(CollisionSide side, Collider *lhs, Collider *rhs)
{
    switch (side) {
        case CollisionSideRight:
            lhs->x = rhs->x - lhs->width;
            break;
        case CollisionSideLeft:
            lhs->x = rhs->x + rhs->width;
            break;
        case CollisionSideTop:
            lhs->y = rhs->y + rhs->height;
            break;
        case CollisionSideBottom:
            lhs->y = rhs->y - lhs->height;
            break;
    }
}
