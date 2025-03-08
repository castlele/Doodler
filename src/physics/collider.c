#include <assert.h>
#include <cstring>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "collider.h"

bool CheckCollision(Collider *lhs, Collider *rhs)
{
    float p1x = fmax(lhs->x, rhs->x);
    float p1y = fmax(lhs->y, rhs->y);
    float p2x = fmin(lhs->x + lhs->width, rhs->x + rhs->width);
    float p2y = fmin(lhs->y + lhs->height, rhs->y + rhs->height);

    return p2x - p1x >= 0 && p2y - p1y >= 0;
}

CollisionSide GetCollisionSide(bool isCollided, Collider *lhs, Collider *rhs)
{
    assert(isCollided);

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

Collider *CreateCollider(float x, float y, float width, float height, ColliderType type)
{
    Collider *collider = malloc(sizeof(Collider));
    collider->x = x;
    collider->y = y;
    collider->width = width;
    collider->height = height;
    collider->speedX = 0;
    collider->speedY = 0;
    collider->type = type;

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
