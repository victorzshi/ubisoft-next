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
        float radius = scene.GetCollider(planet).radius;

        // Bigger planets have more enemies
        int count = 0;
        int enemies = (int)floor(radius * 2.0f);
        total += enemies;
        while (count < enemies)
        {
            Vector3 planetPosition = scene.GetTransform(planet).position;

            Vector3 direction = Utils::RandomUnitCircleVector();
            float distance = radius * Utils::RandomFloat(1.0f, 2.0f);

            Vector3 alienPosition;
            alienPosition = planetPosition + direction * distance;

            // TODO: Check that the alien position isn't inside any other planet

            // TODO: Turret OR flying enemy type.

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