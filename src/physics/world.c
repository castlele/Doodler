#include <stdbool.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "world.h"
#include "collider.h"

// TODO: defines should be deleted or moved to constants
#define MAX_BODIES_COUNT 32
#define MAX_SPEED_Y 250
#define GRAVITY 80

// TODO: This should be refactored!
Collider *bodies[MAX_BODIES_COUNT];
int currentIndex = 0;

typedef enum CollisionSide
{
    CollisionSideTop,
    CollisionSideBottom,
    CollisionSideLeft,
    CollisionSideRight,
} CollisionSide;

bool IsCollided(Collider *lhs, Collider *rhs);
CollisionSide CheckCollision(Collider *lhs, Collider *rhs);

PhysicsWorld CreatePhysicsWorld(int gravityX, int gravityY)
{
    return (PhysicsWorld) {};
}

Collider *AddCollider(ColliderData data)
{
    int len = sizeof(bodies) / sizeof(Collider *);

    if (currentIndex > len) {
        currentIndex = 0;
    }

    Collider *collider = bodies[currentIndex];

    if (collider) {
        DestroyCollider(collider);
        bodies[currentIndex] = NULL;
    }

    collider = CreateCollider(data);

    bodies[currentIndex] = collider;
    currentIndex++;

    return collider;
}

void UpdatePhysicsWorld(PhysicsWorld *w)
{
    float dt = GetFrameTime();

    for (int i = 0; i < currentIndex; i++) {
        Collider *lhs = bodies[i];

        for (int j = 0; j < currentIndex; j++) {
            if (i == j) continue;

            Collider *rhs = bodies[j];

            if (IsCollided(lhs, rhs)) {
                CollisionSide side = CheckCollision(lhs, rhs);

                switch (side) {
                    case CollisionSideBottom:
                    case CollisionSideTop:
                        lhs->speedY = 0;
                        break;
                    default: break;
                }
            }
        }

        if (lhs->type == ColliderTypeDinamic && lhs->speedY != 0) {
            lhs->speedY += dt * GRAVITY;

            lhs->y += fmin(MAX_SPEED_Y, fmax(-MAX_SPEED_Y, lhs->speedY * dt));
        }
    }
}

void DrawPhysicsWorld(PhysicsWorld *w)
{
    for (int i = 0; i < currentIndex; i++) {
        Collider *c = bodies[i];

        DrawRectangleLines(c->x, c->y, c->width, c->height, RED);
    }
}

// Private Methods Declarations

bool IsCollided(Collider *lhs, Collider *rhs)
{
    bool collided = false;
    float p1x = fmax(lhs->x, rhs->x);
    float p1y = fmax(lhs->y, rhs->y);
    float p2x = fmin(lhs->x + lhs->width, rhs->x + rhs->width);
    float p2y = fmin(lhs->y + lhs->height, rhs->y + rhs->height);

    if (p2x - p1x > 0 && p2y - p1y > 0) {
        collided = true;
    }

    return collided;
}

CollisionSide CheckCollision(Collider *lhs, Collider *rhs)
{
    float right = (lhs->x + lhs->width) + rhs->x;
    float left = (rhs->x + rhs->width) + lhs->x;
    float bottom = (lhs->y + lhs->height) + rhs->y;
    float top = (rhs->y + rhs->height) + lhs->y;

    if (right < left && right < top && right < bottom) {
        return CollisionSideRight;
    } else if (left < top && left < bottom) {
        return CollisionSideLeft;
    } else if (top < bottom) {
        return CollisionSideTop;
    } else {
        return CollisionSideBottom;
    }
}
