#ifndef WORLD_H_
#define WORLD_H_

#include "collider.h"

#define MAX_COLLIDERS 100

typedef struct PhysicsWorld
{
    float gravityX;
    float gravityY;
    // TODO: Make array mutable
    Collider *colliders[MAX_COLLIDERS];
    int currentCollider;
} PhysicsWorld;

PhysicsWorld CreatePhysicsWorld(int gravityX, int gravityY);
void AddColliderToWorld(PhysicsWorld *w, Collider *c);

void UpdatePhysicsWorld(PhysicsWorld *w);
void DrawPhysicsWorld(PhysicsWorld *w);

#endif
