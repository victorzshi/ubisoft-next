#include "stdafx.h"

#include "Fuel.h"

#include "Math/Utils/Utils.h"
#include "Scene/Scene.h"

void Fuel::Init(Scene &scene)
{
    int id = 0;
    int total = 0;
    for (auto &planet : scene.GetPlanets().GetIds())
    {
        id = CreateFuel(scene, scene.GetTransform(planet).position);
        total++;
    }

    SetScene(&scene);
    SetBegin(id - (total - 1));
    SetSize(id + 1);
    SetEnd(id);
}

void Fuel::Update(Scene &scene)
{
    int id = GetBegin();
    while (id < GetSize())
    {
        if (scene.GetHealth(id).points <= 0)
        {
            scene.GetParticles().Explode(scene, id);

            Deactivate(id);
        }
        else
        {
            id++;
        }
    }

    UpdateIds();
}

int Fuel::CreateFuel(Scene &scene, Vector3 &position)
{
    int id = scene.CreateId();

    Collider collider;
    collider.radius = 1.0f;
    scene.SetCollider(id, collider);

    Health health;
    health.points = 1;
    scene.SetHealth(id, health);

    Model model;
    model.mesh.SetMesh(Meshes::CUBE);
    model.color.SetColor(Colors::BLUE);
    model.lighting = Lighting::BRIGHT;
    scene.SetModel(id, model);

    Transform transform;
    transform.position = position;
    transform.scaling = Vector3(2.0f, 2.0f, 2.0f);
    transform.rotation.x = Utils::RandomFloat(0.0f, 360.0f);
    transform.rotation.y = Utils::RandomFloat(0.0f, 360.0f);
    transform.rotation.z = Utils::RandomFloat(0.0f, 360.0f);
    scene.SetTransform(id, transform);

    return id;
}