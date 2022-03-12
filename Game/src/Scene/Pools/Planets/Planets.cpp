#include "stdafx.h"

#include "Planets.h"

#include "Math/Utils/Utils.h"
#include "Scene/Scene.h"

void Planets::Init(Scene &scene)
{
    int index = 0;
    int count = 0;
    while (count < TOTAL)
    {
        // Select a different direction for each planet going clockwise
        // Max 8 directions
        int random = Utils::RandomInt(0, 7);
        if (m_random.count(random) == 0)
        {
            m_random.insert(random);

            int id = scene.CreateId();

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
            GeneratePlanet(scene, id, position);

            index = id;
            count++;
        }
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

void Planets::GeneratePlanet(Scene &scene, int id, Vector3 &position)
{
    float scale = Utils::RandomFloat(5.0f, 10.0f);

    AI ai;
    ai.attackRange = scale * 2.0f;
    scene.SetAI(id, ai);

    Model model;
    model.mesh.SetMesh(Meshes::SPHERE);
    model.color.SetColor(Colors::GREEN);
    model.lighting = Lighting::SHADOW;
    scene.SetModel(id, model);

    Transform transform;
    transform.position = position;
    transform.scaling = Vector3(scale, scale, scale);
    scene.SetTransform(id, transform);
}