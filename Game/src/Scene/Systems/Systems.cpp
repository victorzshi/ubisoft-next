#include "stdafx.h"

#include "Systems.h"

#include "Scene/Scene.h"

void Systems::UpdatePosition(Scene &scene, int id, float deltaTime)
{
    Physics physics = scene.GetPhysics(id);
    Transform transform = scene.GetTransform(id);

    transform.position += physics.velocity * deltaTime / 1000.0f;

    float width = 7.0f;
    if (transform.position.x > width)
    {
        transform.position.x = -width;
    }
    else if (transform.position.x < -width)
    {
        transform.position.x = width;
    }

    float height = 4.0f;
    if (transform.position.y > height)
    {
        transform.position.y = -height;
    }
    else if (transform.position.y < -height)
    {
        transform.position.y = height;
    }

    scene.SetTransform(id, transform);
}

void Systems::UpdateRotation(Scene &scene, int id, float deltaTime)
{
    Transform transform = scene.GetTransform(id);

    transform.rotation.x += deltaTime / 100.0f;
    transform.rotation.y += deltaTime / 100.0f;
    transform.rotation.z += deltaTime / 100.0f;

    transform.rotation.x = fmod(transform.rotation.x, 360.0f);
    transform.rotation.y = fmod(transform.rotation.y, 360.0f);
    transform.rotation.z = fmod(transform.rotation.z, 360.0f);

    scene.SetTransform(id, transform);
}