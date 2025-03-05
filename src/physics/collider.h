#ifndef COLLIDER_H_
#define COLLIDER_H_

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

typedef struct ColliderData
{
    float x;
    float y;
    float width;
    float height;
    ColliderType type;
} ColliderData;

Collider *CreateCollider(ColliderData data);
void DestroyCollider(Collider *collider);

#endif
