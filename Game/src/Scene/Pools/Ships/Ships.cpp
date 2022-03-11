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
        model.mesh.SetMesh(Meshes::CONE);
        model.color.SetColor(Colors::BLUE);
        model.lighting = Lighting::SHADOW;
        scene.SetModel(id, model);

        Timer timer;
        timer.start = scene.GetTime();
        scene.SetTimer(id, timer);

        index = id;
    }

    SetScene(&scene);
    SetBegin(index - (TOTAL - 1));
    SetSize(index + 1);
    SetEnd(index);
}

void Ships::Update(Scene &scene)
{
    // TODO: Check ship health.

    UpdateIds();
}

void Ships::ResetBulletCooldown(Scene& scene, int id)
{
    Timer timer = scene.GetTimer(id);
    timer.start = scene.GetTime();
    scene.SetTimer(id, timer);
}