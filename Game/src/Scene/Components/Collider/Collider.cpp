#include "stdafx.h"

#include "Collider.h"

#include "Scene/Scene.h"

Collider::Collider() : radius(0.0f)
{
}

bool Collider::IsHit(Scene &scene, int from, int to)
{
    Vector3 a = scene.GetTransform(from).position;
    Vector3 b = scene.GetTransform(to).position;

    float x = (a.x - b.x) * (a.x - b.x);
    float y = (a.y - b.y) * (a.y - b.y);
    float z = (a.z - b.z) * (a.z - b.z);
    float distance = sqrtf(x + y + z);

    if (distance > scene.GetCollider(from).radius + scene.GetCollider(to).radius)
    {
        return false;
    }
    else
    {
        return true;
    }
}