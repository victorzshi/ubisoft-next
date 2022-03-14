#include "stdafx.h"

#include "Bullets.h"

#include "Scene/Scene.h"

void Bullets::Init(Scene &scene)
{
    int id = 0;
    for (int i = 0; i < TOTAL; i++)
    {
        // Allocate memory
        id = scene.CreateId();
    }

    SetScene(&scene);
    SetBegin(id - (TOTAL - 1));
    SetSize(id - (TOTAL - 1));
    SetEnd(id);
}

void Bullets::Update(Scene &scene)
{
    float current = scene.GetTime();

    int id = GetBegin();
    while (id < GetSize())
    {
        Timer timer = scene.GetTimer(id);

        if (timer.Elapsed(current) >= timer.stayAlive)
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

void Bullets::ShipShootAt(Scene &scene, Vector3 &from, Vector3 &to)
{
    int bullet = GetSize();

    if (Activate(bullet))
    {
        float width = 0.1f;

        Vector3 direction = (to - from).Normalize();
        Vector3 position = from + direction * 0.6f; // Spawn the bullet a little in front of the model

        Collider collider;
        collider.radius = width * 0.5f;
        scene.SetCollider(bullet, collider);

        Model model;
        model.mesh.SetMesh(Meshes::CUBE);
        model.color.SetColor(Colors::WHITE);
        scene.SetModel(bullet, model);

        Health health;
        health.points = 1;
        scene.SetHealth(bullet, health);

        Transform transform;
        transform.position = position;
        transform.scaling = Vector3(width, width, width);
        scene.SetTransform(bullet, transform);

        Physics physics;
        physics.velocity = direction * 15.0f;
        scene.SetPhysics(bullet, physics);

        Timer timer;
        timer.start = scene.GetTime();
        timer.stayAlive = 0.5f;
        scene.SetTimer(bullet, timer);
    }
}

void Bullets::AlienShootAt(Scene &scene, Vector3 &from, Vector3 &to)
{
    int bullet = GetSize();

    if (Activate(bullet))
    {
        float width = 0.5f;

        Vector3 direction = (to - from).Normalize();
        Vector3 position = from + direction; // Spawn the bullet a little in front of the model

        Collider collider;
        collider.radius = width * 0.5f;
        scene.SetCollider(bullet, collider);

        Model model;
        model.mesh.SetMesh(Meshes::CUBE);
        model.color.SetColor(Colors::RED);
        scene.SetModel(bullet, model);

        Health health;
        health.points = 1;
        scene.SetHealth(bullet, health);

        Transform transform;
        transform.position = position;
        transform.scaling = Vector3(width, width, width);
        scene.SetTransform(bullet, transform);

        Physics physics;
        physics.velocity = direction * 5.0f;
        scene.SetPhysics(bullet, physics);

        Timer timer;
        timer.start = scene.GetTime();
        timer.stayAlive = 2.0f;
        scene.SetTimer(bullet, timer);
    }
}