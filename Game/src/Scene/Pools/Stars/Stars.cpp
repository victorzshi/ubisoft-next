#include "stdafx.h"

#include "Stars.h"

#include "Math/Utils/Utils.h"
#include "Scene/Scene.h"

void Stars::Init(Scene &scene)
{
    int index = 0;
    for (int i = 0; i < TOTAL; i++)
    {
        int id = scene.CreateId();

        Model model;
        model.mesh.SetMesh(Meshes::PLANE);
        model.color.SetColor(Colors::WHITE);
        model.lighting = Lighting::SHADOW;
        scene.SetModel(id, model);

        float x = Utils::RandomFloat(-300.0f, 300.0f);
        float y = Utils::RandomFloat(-300.0f, 300.0f);
        float z = Utils::RandomFloat(-100.0f, -75.0f);

        Transform transform;
        transform.position = Vector3(x, y, z);
        // Reflect different amounts of light
        transform.rotation.x = 90.0f + Utils::RandomFloat(-90.0f, 90.0f);
        transform.scaling = Vector3(0.1f, 0.1f, 0.1f);
        scene.SetTransform(id, transform);

        index = id;
    }

    SetScene(&scene);
    SetBegin(index - (TOTAL - 1));
    SetSize(index + 1);
    SetEnd(index);
}

void Stars::Update(Scene &scene)
{
    UpdateIds();
}