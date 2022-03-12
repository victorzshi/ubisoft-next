#include "stdafx.h"

#include "Bullets.h"

#include "Scene/Scene.h"

void Bullets::Init(Scene &scene)
{
    int index = 0;
    for (int i = 0; i < TOTAL; i++)
    {
        int id = scene.CreateId();

        Collider collider;
        collider.radius = WIDTH / 2.0f;
        scene.SetCollider(id, collider);

        Health health;
        health.points = 1;
        scene.SetHealth(id, health);

        Model model;
        model.mesh.SetMesh(Meshes::CUBE);
        scene.SetModel(id, model);

        Transform transform;
        transform.scaling = Vector3(WIDTH, WIDTH, WIDTH);
        scene.SetTransform(id, transform);

        index = id;
    }

    SetScene(&scene);
    SetBegin(index - (TOTAL - 1));
    SetSize(index - (TOTAL - 1));
    SetEnd(index);
}

void Bullets::Update(Scene &scene)
{
    float current = scene.GetTime();

    int id = GetBegin();
    while (id < GetSize())
    {
        if (scene.GetTimer(id).Elapsed(current) >= DURATION)
        {
            Deactivate(id);
        }
        else if (scene.GetHealth(id).points <= 0)
        {
            Deactivate(id);
        }
        else
        {
            id++;
        }
    }

    UpdateIds();
}

void Bullets::ShootAt(Scene &scene, Vector3 &from, Vector3 &to, Colors color)
{
    int bullet = GetSize();

    if (Activate(bullet))
    {
        Vector3 direction = (to - from).Normalize();
        Vector3 position = from + direction; // Spawn the bullet a little in front of the model

        Model model = scene.GetModel(bullet);
        model.color.SetColor(color);
        scene.SetModel(bullet, model);

        Health health = scene.GetHealth(bullet);
        health.points = 1;
        scene.SetHealth(bullet, health);

        Transform transform = scene.GetTransform(bullet);
        transform.position = position;
        transform.scaling = Vector3(0.1f, 0.1f, 0.1f);
        scene.SetTransform(bullet, transform);

        Physics physics = scene.GetPhysics(bullet);
        physics.velocity = direction * DELTA_VELOCITY;
        scene.SetPhysics(bullet, physics);

        Timer timer = scene.GetTimer(bullet);
        timer.start = scene.GetTime();
        scene.SetTimer(bullet, timer);
    }
}