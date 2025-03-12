#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "collider.h"

bool CheckCollision(Collider *lhs, Collider *rhs)
{
    if (!lhs->active || !rhs->active) {
        return false;
    }

    float pmaxX = fmax(lhs->position.x, rhs->position.x);
    float pmaxY = fmax(lhs->position.y, rhs->position.y);
    float pminX = fmin(lhs->position.x + lhs->width, rhs->position.x + rhs->width);
    float pminY = fmin(lhs->position.y + lhs->height, rhs->position.y + rhs->height);

    return pminX - pmaxX >= 0 && pminY - pmaxY >= 0;
}

CollisionSide GetCollisionSide(bool isCollided, Collider *lhs, Collider *rhs)
{
    assert(isCollided);

    float right = (lhs->position.x + lhs->width) - rhs->position.x;
    float left = (rhs->position.x + rhs->width) - lhs->position.x;
    float top = (rhs->position.y + rhs->height) - lhs->position.y;
    float bottom = (lhs->position.y + lhs->height) - rhs->position.y;

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

Collider *CreateCollider(float x, float y, float width, float height, ColliderType type, float mass)
{
    Collider *collider = malloc(sizeof(Collider));
    collider->position = (Vector2) { .x = x, .y = y, };
    collider->width = width;
    collider->height = height;
    collider->velocity = (Vector2) { .x = 0, .y = 0, };
    collider->force = (Vector2) { .x = 0, .y = 0, };
    collider->mass = mass;
    collider->type = type;
    collider->active = true;

    return collider;
}

void SetColliderMask(Collider *c, char mask[])
{
    strcpy(c->mask, mask);
}

void DestroyCollider(Collider *collider)
{
    free(collider);
}
