#ifndef WORLD_H_
#define WORLD_H_

#include "collider.h"

typedef struct PhysicsWorld
{
} PhysicsWorld;

PhysicsWorld CreatePhysicsWorld(int gravityX, int gravityY);
Collider *AddCollider(ColliderData data);

void UpdatePhysicsWorld(PhysicsWorld *w);
void DrawPhysicsWorld(PhysicsWorld *w);

#endif
