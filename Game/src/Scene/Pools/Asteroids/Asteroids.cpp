#include "stdafx.h"

#include "Asteroids.h"

#include "Math/Random/Random.h"
#include "Scene/Scene.h"

void Asteroids::Init(Scene &scene)
{
    Mesh mesh = Mesh::LoadFromObjectFile(file);

    int index = 0;
    for (int i = 0; i < TOTAL; i++)
    {
        int id = scene.CreateId();

        scene.SetMesh(id, mesh);

        Physics physics;
        physics.velocity.x = Random::GetFloat(-1.0f, 1.0f);
        physics.velocity.y = Random::GetFloat(-1.0f, 1.0f);
        scene.SetPhysics(id, physics);

        Transform transform;
        transform.rotation.x = Random::GetFloat(0.0f, 360.0f);
        transform.rotation.y = Random::GetFloat(0.0f, 360.0f);
        transform.rotation.z = Random::GetFloat(0.0f, 360.0f);
        transform.scaling = Vector3(0.5f, 0.5f, 0.5f);
        scene.SetTransform(id, transform);

        index = id;
    }

    SetScene(&scene);
    SetBegin(index - (TOTAL - 1));
    SetSize(index + 1);
    SetEnd(index);
}