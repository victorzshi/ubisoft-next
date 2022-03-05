#include "stdafx.h"

#include "Asteroids.h"

#include "Scene/Scene.h"

void Asteroids::Init(Scene &scene)
{
    Mesh mesh = Mesh::LoadFromObjectFile(file);

    int index = 0;
    for (int i = 0; i < total; i++)
    {
        int id = scene.CreateId();

        // Need to generate random position
        Transform transform;
        transform.position = Vector3(0.0f, (float)i, 0.0f);
        scene.SetTransform(id, transform);

        scene.SetMesh(id, mesh);

        index = id;
    }

    SetScene(&scene);
    SetBegin(index - (total - 1));
    SetSize(index + 1);
    SetEnd(index);
}