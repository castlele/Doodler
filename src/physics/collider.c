#include <stdlib.h>

#include "collider.h"

Collider *CreateCollider(ColliderData data)
{
    Collider *collider = malloc(sizeof(Collider));
    collider->x = data.x;
    collider->y = data.y;
    collider->width = data.width;
    collider->height = data.height;
    collider->speedY = 0;
    collider->type = data.type;

    return collider;
}

void DestroyCollider(Collider *collider)
{
    free(collider);
}
