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
    float speedY;
    ColliderType type;
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
void DestroyCollider(Collider *collider);

#endif
