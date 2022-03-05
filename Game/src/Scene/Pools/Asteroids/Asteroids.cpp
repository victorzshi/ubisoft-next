#include "stdafx.h"

#include "Asteroids.h"

#include "Scene/Components/Mesh/Mesh.h"
#include "Scene/Components/Transform/Transform.h"
#include "Scene/Scene.h"

void Asteroids::Init(Scene& scene)
{
    SetScene(&scene);

    Mesh *meshes = scene.GetMeshes();
    Transform *transforms = scene.GetTransforms();

    Mesh mesh = Mesh::LoadFromObjectFile("sphere.obj");

    size_t index = 0;
    size_t total = 5;
    for (int i = 0; i < total; i++)
    {
        size_t id = scene.CreateEntity();

        // Need to generate random position
        transforms[id].position = Vector3(0.0f, (float)i, 0.0f);

        meshes[id] = mesh;

        index = id;
    }

    m_begin = index - (total - 1);
    m_size = index + 1;
    m_end = index;
}