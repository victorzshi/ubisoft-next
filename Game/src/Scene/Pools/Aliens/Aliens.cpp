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

            if (Utils::RandomFloat(0.0f, 1.0f) > 0.3f)
            {
                id = CreateTurret(scene, alienPosition);
            }
            else
            {
                id = CreateBomber(scene, alienPosition);
            }

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
        Timer timer = scene.GetTimer(id);

        if (scene.GetHealth(id).points <= 0)
        {
            scene.GetParticles().Explode(scene, id);

            Deactivate(id);

            scene.GetUI()->scoring.enemiesDestroyed++;
        }
        else if (timer.stayAlive != 0.0f && timer.Elapsed(scene.GetTime()) > timer.stayAlive)
        {
            scene.GetParticles().Explode(scene, id);

            Deactivate(id);

            scene.GetUI()->scoring.enemiesDestroyed++;
        }
        else
        {
            id++;
        }
    }

    UpdateIds();
}

int Aliens::CreateTurret(Scene &scene, Vector3 &position)
{
    int id = scene.CreateId();

    float width = 2.0f;

    AI ai;
    ai.attackRange = 12.0f;
    scene.SetAI(id, ai);

    Collider collider;
    collider.radius = width * 0.5f;
    scene.SetCollider(id, collider);

    Health health;
    health.points = 50;
    scene.SetHealth(id, health);

    Model model;
    model.mesh.SetMesh(Meshes::TORUS);
    model.color.SetColor(Colors::RED);
    model.lighting = Lighting::OUTLINE;
    scene.SetModel(id, model);

    Timer timer;
    timer.cooldown = 0.2f;
    scene.SetTimer(id, timer);

    Transform transform;
    transform.position = position;
    transform.rotation.x = Utils::RandomFloat(0.0f, 360.0f);
    transform.rotation.y = Utils::RandomFloat(0.0f, 360.0f);
    transform.rotation.z = Utils::RandomFloat(0.0f, 360.0f);
    transform.scaling = Vector3(width, width, width);
    scene.SetTransform(id, transform);

    return id;
}

int Aliens::CreateBomber(Scene &scene, Vector3 &position)
{
    int id = scene.CreateId();

    float width = 0.5f;

    AI ai;
    ai.attackRange = 8.0f;
    ai.isBomber = true;
    scene.SetAI(id, ai);

    Collider collider;
    collider.radius = width * 0.5f;
    scene.SetCollider(id, collider);

    Health health;
    health.points = 1;
    scene.SetHealth(id, health);

    Model model;
    model.mesh.SetMesh(Meshes::MONKEY);
    model.color.SetColor(Colors::RED);
    model.lighting = Lighting::OUTLINE;
    scene.SetModel(id, model);

    Transform transform;
    transform.position = position;
    transform.rotation.x = Utils::RandomFloat(0.0f, 360.0f);
    transform.rotation.y = Utils::RandomFloat(0.0f, 360.0f);
    transform.rotation.z = Utils::RandomFloat(0.0f, 360.0f);
    transform.scaling = Vector3(width, width, width);
    scene.SetTransform(id, transform);

    return id;
}
