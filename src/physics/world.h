#ifndef WORLD_H_
#define WORLD_H_

#include <raylib.h>
#include "collider.h"

#define MAX_COLLIDERS 100

typedef struct PhysicsWorld
{
    Vector2 gravity;
    // TODO: Make array mutable
    Collider *colliders[MAX_COLLIDERS];
    int currentCollider;
} PhysicsWorld;

PhysicsWorld CreatePhysicsWorld(int gravityX, int gravityY);
void AddColliderToWorld(PhysicsWorld *w, Collider *c);

void UpdatePhysicsWorld(PhysicsWorld *w, float dt);
void DrawPhysicsWorld(PhysicsWorld *w);

#endif
