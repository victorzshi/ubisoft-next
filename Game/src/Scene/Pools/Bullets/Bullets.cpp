#include "stdafx.h"

#include "Bullets.h"

#include "Scene/Scene.h"

void Bullets::Init(Scene &scene)
{
    int index = 0;
    for (int i = 0; i < TOTAL; i++)
    {
        int id = scene.CreateId();

        Model model;
        model.mesh.SetMesh(Meshes::CUBE);
        model.color.SetColor(Colors::GREEN);
        scene.SetModel(id, model);

        Transform transform;
        transform.scaling = Vector3(0.1f, 0.1f, 0.1f);
        scene.SetTransform(id, transform);

        index = id;
    }

    SetScene(&scene);
    SetBegin(index - (TOTAL - 1));
    SetSize(index - (TOTAL - 1));
    SetEnd(index);
}

void Bullets::Update(Scene &scene)
{
    float current = scene.GetTime();

    for (int id = GetBegin(); id < GetSize(); id++)
    {
        if (scene.GetTimer(id).Elapsed(current) >= DURATION)
        {
            Deactivate(id);
        }
    }

    UpdateIds();
}

void Bullets::CreateBullet(Scene &scene, Vector3 &position, Vector3 &direction)
{
    int id = GetSize();

    if (Activate(id))
    {
        Transform transform = scene.GetTransform(id);
        transform.position = position;
        transform.scaling = Vector3(0.1f, 0.1f, 0.1f);
        scene.SetTransform(id, transform);

        Physics physics = scene.GetPhysics(id);
        physics.velocity = direction * DELTA_VELOCITY;
        scene.SetPhysics(id, physics);

        Timer timer = scene.GetTimer(id);
        timer.start = scene.GetTime();
        scene.SetTimer(id, timer);
    }
}