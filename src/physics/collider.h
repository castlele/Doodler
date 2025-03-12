#ifndef COLLIDER_H_
#define COLLIDER_H_

#include <raylib.h>
#include <stdbool.h>

typedef enum ColliderType
{
    ColliderTypeStatic,
    ColliderTypeDinamic,
} ColliderType;

typedef struct Collider
{
    Vector2 position;
    float width;
    float height;
    Vector2 velocity;
    Vector2 force;
    float mass;
    ColliderType type;
    char mask[16];

    bool active;
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

Collider *CreateCollider(float x, float y, float width, float height, ColliderType type, float mass);
void SetColliderMask(Collider *c, char mask[]);
void DestroyCollider(Collider *collider);

#endif
