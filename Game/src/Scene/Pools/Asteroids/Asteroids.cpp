#include "stdafx.h"

#include "Asteroids.h"

#include "Math/Utils/Utils.h"
#include "Scene/Scene.h"

void Asteroids::Init(Scene &scene)
{
    int index = 0;
    for (int i = 0; i < TOTAL; i++)
    {
        int id = scene.CreateId();

        float scale = Utils::RandomFloat(1.0f, 2.0f);

        Collider collider;
        collider.radius = scale / 2.0f;
        scene.SetCollider(id, collider);

        Health health;
        health.points = HEALTH;
        scene.SetHealth(id, health);

        Model model;
        model.mesh.SetMesh(Meshes::ICOSPHERE);
        model.color.SetColor(Colors::GREY);
        model.lighting = Lighting::SHADOW;
        scene.SetModel(id, model);

        Physics physics;
        physics.velocity.x = Utils::RandomFloat(-1.0f, 1.0f);
        physics.velocity.y = Utils::RandomFloat(-1.0f, 1.0f);
        scene.SetPhysics(id, physics);

        Transform transform;
        transform.position.x = Utils::RandomFloat(-20.0f, 20.0f);
        transform.position.y = Utils::RandomFloat(-20.0f, 20.0f);
        transform.rotation.x = Utils::RandomFloat(0.0f, 360.0f);
        transform.rotation.y = Utils::RandomFloat(0.0f, 360.0f);
        transform.rotation.z = Utils::RandomFloat(0.0f, 360.0f);
        transform.scaling = Vector3(scale, scale, scale);
        scene.SetTransform(id, transform);

        index = id;
    }

    SetScene(&scene);
    SetBegin(index - (TOTAL - 1));
    SetSize(index + 1);
    SetEnd(index);
}

void Asteroids::Update(Scene &scene)
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