#include "stdafx.h"

#include "Asteroids.h"

#include "Math/Random/Random.h"
#include "Scene/Scene.h"

void Asteroids::Init(Scene &scene)
{
    Mesh mesh = Mesh::LoadFromObjectFile(file);

    int index = 0;
    for (int i = 0; i < total; i++)
    {
        int id = scene.CreateId();

        Transform transform;
        transform.position.x = Random::GetFloat(-5.0f, 5.0f);
        transform.position.y = Random::GetFloat(-5.0f, 5.0f);
        scene.SetTransform(id, transform);

        scene.SetMesh(id, mesh);

        index = id;
    }

    SetScene(&scene);
    SetBegin(index - (total - 1));
    SetSize(index + 1);
    SetEnd(index);
}