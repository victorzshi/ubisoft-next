#include "stdafx.h"

#include "Aliens.h"

#include "Math/Utils/Utils.h"
#include "Scene/Scene.h"

void Aliens::Init(Scene &scene)
{
    int id = 0;
    int total = 0;
    for (auto &planet : scene.GetPlanets().GetIds())
    {
        Transform transform = scene.GetTransform(planet);

        // Bigger planets have more enemies
        int count = 0;
        int enemies = (int)floor(transform.scaling.x);
        total += enemies;
        while (count < enemies)
        {
            Vector3 planetPosition = transform.position;

            Vector3 direction = Utils::RandomUnitCircleVector();
            // float distance = transform.scaling.x * Utils::RandomFloat(0.6f, 1.5f);
            float radius = transform.scaling.x * 0.5f;

            Vector3 alienPosition;
            alienPosition = planetPosition + direction * radius;

            // TODO: Check that the alien position isn't inside any other planet

            id = CreateAlien(scene, alienPosition);
            count++;
        }
    }

    SetScene(&scene);
    SetBegin(id - (total - 1));
    SetSize(id + 1);
    SetEnd(id);
}

void Aliens::Update(Scene &scene)
{
    int id = GetBegin();
    while (id < GetSize())
    {
        if (scene.GetHealth(id).points <= 0)
        {
            scene.GetParticles().Explosion(scene, id);

            Deactivate(id);
        }
        else
        {
            id++;
        }
    }

    UpdateIds();
}

int Aliens::CreateAlien(Scene &scene, Vector3 &position)
{
    int id = scene.CreateId();

    AI ai;
    ai.attackRange = 10.0f;
    scene.SetAI(id, ai);

    Collider collider;
    collider.radius = 0.5f;
    scene.SetCollider(id, collider);

    Health health;
    health.points = 10;
    scene.SetHealth(id, health);

    Model model;
    model.mesh.SetMesh(Meshes::MONKEY);
    model.color.SetColor(Colors::RED);
    model.lighting = Lighting::OUTLINE;
    scene.SetModel(id, model);

    Transform transform;
    transform.position = position;
    scene.SetTransform(id, transform);

    return id;
}