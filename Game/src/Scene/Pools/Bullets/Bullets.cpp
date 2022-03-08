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
        model.mesh = Mesh::CUBE;
        model.color = Color::WHITE;
        model.light = Light::BRIGHT;
        scene.SetModel(id, model);

        Transform transform;
        transform.scaling = Vector3(0.2f, 0.2f, 0.2f);
        scene.SetTransform(id, transform);

        index = id;
    }

    SetScene(&scene);
    SetBegin(index - (TOTAL - 1));
    SetSize(index - (TOTAL - 1));
    SetEnd(index);
}

void Bullets::CreateBullet(Vector3 position)
{
    int id = GetNextId();

    if (Activate(id))
    {
        Transform transform = GetScene()->GetTransform(id);
        transform.position = position;
        GetScene()->SetTransform(id, transform);
    }
}