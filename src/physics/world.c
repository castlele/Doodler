#include <stdbool.h>
#include <raylib.h>
#include <raymath.h>
#include <assert.h>

#include "world.h"
#include "collider.h"

void BumpColliders(CollisionSide side, Collider *lhs, Collider *rhs);

PhysicsWorld CreatePhysicsWorld(int gravityX, int gravityY)
{
    return (PhysicsWorld) {
        .gravity = (Vector2) { .x = gravityX, .y = gravityY, },
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
                // TODO: This method is useless right now, because it's working incorrectly,
                // Maybe this is caused by setting fps in `main.c`
                // BumpColliders(side, lhs, rhs);

                switch (side) {
                    case CollisionSideTop: break;
                    case CollisionSideBottom:
                        // TODO: This should be set differently!
                        lhs->velocity.y = -650;
                        break;
                    case CollisionSideRight:
                    case CollisionSideLeft:
                        lhs->velocity.x = 0;
                        break;
                }
            }
        }

        lhs->force = Vector2Add(lhs->force, Vector2Scale(w->gravity, lhs->mass));

        Vector2 a = (Vector2) { .x = lhs->force.x / lhs->mass, .y = lhs->force.y / lhs->mass, };
        lhs->velocity = Vector2Add(lhs->velocity, Vector2Scale(a, dt));

        lhs->position = Vector2Add(lhs->position, Vector2Scale(lhs->velocity, dt));

        lhs->force = (Vector2) { .x = 0, .y = 0 };
    }
}

void DrawPhysicsWorld(PhysicsWorld *w)
{
    for (int i = 0; i <= w->currentCollider; i++) {
        Collider *c = w->colliders[i];

        DrawRectangleLines(c->position.x, c->position.y, c->width, c->height, RED);
    }
}

// Private declarations

void BumpColliders(CollisionSide side, Collider *lhs, Collider *rhs)
{
    switch (side) {
        case CollisionSideRight:
            lhs->position.x = rhs->position.x - lhs->width;
            break;
        case CollisionSideLeft:
            lhs->position.x = rhs->position.x + rhs->width;
            break;
        case CollisionSideTop:
            lhs->position.y = rhs->position.y + rhs->height;
            break;
        case CollisionSideBottom:
            lhs->position.y = rhs->position.y - lhs->height;
            break;
    }
}
