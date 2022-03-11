#include "stdafx.h"

#include "Aliens.h"

#include "Math/Random/Random.h"
#include "Scene/Scene.h"

void Aliens::Init(Scene &scene)
{
    int index = 0;
    for (int i = 0; i < TOTAL; i++)
    {
        int id = scene.CreateId();

        AI ai;
        ai.attackRange = 5.0f;
        scene.SetAI(id, ai);

        Collider collider;
        collider.radius = WIDTH / 2.0f;
        scene.SetCollider(id, collider);

        Health health;
        health.points = HEALTH_POINTS;
        scene.SetHealth(id, health);

        Model model;
        model.mesh.SetMesh(Meshes::MONKEY);
        model.color.SetColor(Colors::PURPLE);
        model.lighting = Lighting::OUTLINE;
        scene.SetModel(id, model);

        Transform transform;
        transform.position.x = Random::GetFloat(-10.0f, 10.0f);
        transform.position.y = Random::GetFloat(-10.0f, 10.0f);
        scene.SetTransform(id, transform);

        index = id;
    }

    SetScene(&scene);
    SetBegin(index - (TOTAL - 1));
    SetSize(index + 1);
    SetEnd(index);
}

void Aliens::Update(Scene &scene)
{
    int id = GetBegin();
    while (id < GetSize())
    {
        if (scene.GetHealth(id).points <= 0)
        {
            scene.GetParticles().CreateBigExplosion(scene, id);

            Deactivate(id);
        }
        else
        {
            id++;
        }
    }

    UpdateIds();
}