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
        int count = 0;
        int enemies = scene.GetAI(planet).enemyCount;
        total += enemies;
        while (count < enemies)
        {
            Vector3 planetPosition = scene.GetTransform(planet).position;

            Vector3 direction = Utils::RandomUnitCircleVector();
            float distance = scene.GetCollider(planet).radius * Utils::RandomFloat(1.5f, 3.0f);

            Vector3 alienPosition;
            alienPosition = planetPosition + direction * distance;

            // TODO: Check that the alien position isn't inside any other planet

            // TODO: Turret OR flying enemy type.

            id = CreateAlien(scene, alienPosition, planet);
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

            int planet = scene.GetAI(id).homePlanet;
            AI ai = scene.GetAI(planet);
            ai.enemyCount--;
            scene.SetAI(planet, ai);

            Deactivate(id);
        }
        else
        {
            id++;
        }
    }

    UpdateIds();
}

int Aliens::CreateAlien(Scene &scene, Vector3 &position, int &planet)
{
    int id = scene.CreateId();

    AI ai;
    ai.attackRange = 10.0f;
    ai.homePlanet = planet;
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