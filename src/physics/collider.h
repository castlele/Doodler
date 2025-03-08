#ifndef COLLIDER_H_
#define COLLIDER_H_

#include <stdbool.h>

typedef enum ColliderType
{
    ColliderTypeStatic,
    ColliderTypeDinamic,
} ColliderType;

typedef struct Collider
{
    float x;
    float y;
    float width;
    float height;
    float speedX;
    float speedY;
    ColliderType type;
    char mask[16];
} Collider;

typedef enum CollisionSide
{
    CollisionSideTop,
    CollisionSideBottom,
    CollisionSideLeft,
    CollisionSideRight,
} CollisionSide;

bool CheckCollision(Collider *lhs, Collider *rhs);
CollisionSide GetCollisionSide(bool isCollided, Collider *lhs, Collider *rhs);

Collider *CreateCollider(float x, float y, float width, float height, ColliderType type);
void SetColliderMask(Collider *c, char mask[]);
void DestroyCollider(Collider *collider);

#endif
