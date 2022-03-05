#include "stdafx.h"

#include "Asteroids.h"

#include "Scene/Components/Mesh/Mesh.h"
#include "Scene/Components/Transform/Transform.h"
#include "Scene/Scene.h"

void Asteroids::Init(Scene &scene)
{
    Mesh *meshes = scene.GetMeshes();
    Transform *transforms = scene.GetTransforms();

    Mesh mesh = Mesh::LoadFromObjectFile(file);

    size_t index = 0;
    for (int i = 0; i < total; i++)
    {
        size_t id = scene.CreateEntity();

        // Need to generate random position
        transforms[id].position = Vector3(0.0f, (float)i, 0.0f);

        meshes[id] = mesh;

        index = id;
    }

    SetScene(&scene);
    SetBegin(index - (total - 1));
    SetSize(index + 1);
    SetEnd(index);
}