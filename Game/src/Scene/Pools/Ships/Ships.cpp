#include "stdafx.h"

#include "Ships.h"

#include "Scene/Scene.h"

void Ships::Init(Scene &scene)
{
    int index = 0;
    for (int i = 0; i < TOTAL; i++)
    {
        int id = scene.CreateId();

        Model model;
        model.mesh.SetMesh(Meshes::SPHERE); 
        model.color = Color::ORANGE;
        model.light = Light::OUTLINE;
        scene.SetModel(id, model);

        index = id;
    }

    SetScene(&scene);
    SetBegin(index - (TOTAL - 1));
    SetSize(index + 1);
    SetEnd(index);
}