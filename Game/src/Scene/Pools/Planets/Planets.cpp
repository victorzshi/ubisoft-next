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

            float x = Utils::RandomFloat(10.0f, 30.0f);
            float y = Utils::RandomFloat(10.0f, 30.0f);
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
    UpdateIds();
}

int Planets::CreatePlanet(Scene &scene, Vector3 &position)
{
    int id = scene.CreateId();

    float scale = Utils::RandomFloat(5.0f, 10.0f);

    AI ai;
    ai.attackRange = scale * 2.0f; // For gravity
    scene.SetAI(id, ai);

    Collider collider;
    collider.radius = scale * 0.5f;
    scene.SetCollider(id, collider);

    Model model;
    model.mesh.SetMesh(Meshes::SPHERE);
    model.color.SetColor(Colors::GREEN);
    model.lighting = Lighting::SHADOW;
    scene.SetModel(id, model);

    Transform transform;
    transform.position = position;
    transform.scaling = Vector3(scale, scale, scale);
    scene.SetTransform(id, transform);

    return id;
}