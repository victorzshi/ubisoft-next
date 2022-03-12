#include "stdafx.h"

#include "Planets.h"

#include "Math/Utils/Utils.h"
#include "Scene/Scene.h"

void Planets::Init(Scene &scene)
{
    int index = 0;
    for (int i = 0; i < TOTAL; i++)
    {
        int id = scene.CreateId();

        float scale = Utils::RandomFloat(5.0f, 10.0f);

        Model model;
        model.mesh.SetMesh(Meshes::SPHERE);
        model.color.SetColor(Colors::GREEN);
        model.lighting = Lighting::SHADOW;
        scene.SetModel(id, model);

        Transform transform;
        transform.position.x = Utils::RandomFloat(-20.0f, 20.0f);
        transform.position.y = Utils::RandomFloat(-20.0f, 20.0f);
        transform.scaling = Vector3(scale, scale, scale);
        scene.SetTransform(id, transform);

        index = id;
    }

    SetScene(&scene);
    SetBegin(index - (TOTAL - 1));
    SetSize(index + 1);
    SetEnd(index);
}

void Planets::Update(Scene &scene)
{
    UpdateIds();
}