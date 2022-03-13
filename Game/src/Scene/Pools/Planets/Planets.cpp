#include "stdafx.h"

#include "Planets.h"

#include "Math/Utils/Utils.h"
#include "Scene/Scene.h"

void Planets::Init(Scene &scene)
{
    int id = 0;
    int count = 0;
    while (count < TOTAL)
    {
        // Select a different direction for each planet going clockwise
        // Max 8 directions
        int random = Utils::RandomInt(0, 7);
        if (m_random.count(random) == 0)
        {
            m_random.insert(random);

            float x = Utils::RandomFloat(20.0f, 40.0f);
            float y = Utils::RandomFloat(20.0f, 40.0f);
            float radius = sqrtf(x * x + y * y);

            switch (random)
            {
            case 0:
                x = -x;
                y = -y;
                break;

            case 1:
                x = 0.0f;
                y = -radius;
                break;

            case 2:
                x = x;
                y = -y;
                break;

            case 3:
                x = radius;
                y = 0.0f;
                break;

            case 4:
                x = x;
                y = y;
                break;

            case 5:
                x = 0.0f;
                y = radius;
                break;

            case 6:
                x = -x;
                y = y;
                break;

            case 7:
                x = -radius;
                y = 0.0f;
                break;

            default:
                x = 0.0f;
                y = 0.0f;
                break;
            }

            Vector3 position = Vector3(x, y, 0.0f);

            id = CreatePlanet(scene, position);
            count++;
        }
    }

    SetScene(&scene);
    SetBegin(id - (TOTAL - 1));
    SetSize(id + 1);
    SetEnd(id);

    // Aliens require planet data
    UpdateIds();
}

void Planets::Update(Scene &scene)
{
    int id = GetBegin();
    while (id < GetSize())
    {
        bool hasEnemies = false;

        for (auto &alien : scene.GetAliens().GetIds())
        {
            Vector3 alienPosition = scene.GetTransform(alien).position;
            Vector3 planetPosition = scene.GetTransform(id).position;

            if (Utils::Distance(alienPosition, planetPosition) <= scene.GetCollider(id).radius * 3.0f)
            {
                hasEnemies = true;
                id++;
                break;
            }
        }

        if (!hasEnemies)
        {
            scene.GetParticles().Explode(scene, id);
            
            Deactivate(id);
        }
    }

    UpdateIds();
}

int Planets::CreatePlanet(Scene &scene, Vector3 &position)
{
    int id = scene.CreateId();

    float scale = Utils::RandomFloat(5.0f, 10.0f);

    AI ai;
    ai.attackRange = scale * 2.0f;    // For gravity
    ai.enemyCount = (int)ceil(scale); // Bigger planets have more enemies
    scene.SetAI(id, ai);

    Collider collider;
    collider.radius = scale * 0.5f;
    scene.SetCollider(id, collider);

    Model model;
    model.mesh.SetMesh(Meshes::ICOSPHERE);
    model.color.SetColor(Colors::GREEN);
    model.lighting = Lighting::SHADOW;
    scene.SetModel(id, model);

    Transform transform;
    transform.position = position;
    transform.scaling = Vector3(scale, scale, scale);
    transform.rotation.y = Utils::RandomFloat(0.0f, 360.0f);
    transform.rotation.x = Utils::RandomFloat(0.0f, 360.0f);
    transform.rotation.z = Utils::RandomFloat(0.0f, 360.0f);
    scene.SetTransform(id, transform);

    return id;
}