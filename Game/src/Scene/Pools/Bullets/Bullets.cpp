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
        model.color = Color::PURPLE;
        model.light = Light::BRIGHT;
        scene.SetModel(id, model);

        index = id;
    }

    SetScene(&scene);
    SetBegin(index - (TOTAL - 1));
    SetSize(index - (TOTAL - 1));
    SetEnd(index);
}

void Bullets::CreateBullet(Vector3 position, Vector3 direction)
{
    int id = GetSize();

    if (Activate(id))
    {
        Transform transform;
        transform.position = position;
        transform.scaling = Vector3(0.1f, 0.1f, 0.1f);
        GetScene()->SetTransform(id, transform);

        Physics physics;
        physics.velocity = direction * DELTA_VELOCITY;
        GetScene()->SetPhysics(id, physics);

        Timer timer;
        timer.start = GetScene()->GetTime();
        GetScene()->SetTimer(id, timer);
    }
}