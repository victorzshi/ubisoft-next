#include "stdafx.h"

#include "Ships.h"

#include "Scene/Scene.h"

void Ships::Init(Scene &scene)
{
    Mesh mesh = Mesh::LoadFromObjectFile(FILE);

    int index = 0;
    for (int i = 0; i < TOTAL; i++)
    {
        int id = scene.CreateId();

        scene.SetMesh(id, mesh);

        index = id;
    }

    SetScene(&scene);
    SetBegin(index - (TOTAL - 1));
    SetSize(index + 1);
    SetEnd(index);
}