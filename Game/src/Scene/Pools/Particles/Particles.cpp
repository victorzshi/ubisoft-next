#include "stdafx.h"

#include "Particles.h"

#include "Math/Utils/Utils.h"
#include "Scene/Scene.h"

void Particles::Init(Scene &scene)
{
    int index = 0;
    for (int i = 0; i < TOTAL; i++)
    {
        int id = scene.CreateId();

        index = id;
    }

    SetScene(&scene);
    SetBegin(index - (TOTAL - 1));
    SetSize(index - (TOTAL - 1));
    SetEnd(index);
}

void Particles::Update(Scene &scene)
{
    float current = scene.GetTime();

    int id = GetBegin();
    while (id < GetSize())
    {
        if (scene.GetTimer(id).Elapsed(current) >= DURATION)
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

void Particles::Ricochet(Scene &scene, int id)
{
    Transform transform = scene.GetTransform(id);
    Model model = scene.GetModel(id);
    Physics physics = scene.GetPhysics(id);
    Timer timer = scene.GetTimer(id);
    timer.start = scene.GetTime();

    for (int i = 0; i < 5; i++)
    {
        int particle = GetSize();

        if (Activate(particle))
        {
            scene.SetModel(particle, model);

            float scale = Utils::RandomFloat(0.0f, 0.1f);
            transform.scaling = Vector3(scale, scale, scale);
            transform.rotation.x = Utils::RandomFloat(0.0f, 360.0f);
            transform.rotation.y = Utils::RandomFloat(0.0f, 360.0f);
            transform.rotation.z = Utils::RandomFloat(0.0f, 360.0f);
            scene.SetTransform(particle, transform);

            physics.velocity.x = Utils::RandomFloat(-5.0f, 5.0f);
            physics.velocity.y = Utils::RandomFloat(-5.0f, 5.0f);
            physics.velocity.z = Utils::RandomFloat(-2.0f, 2.0f);
            scene.SetPhysics(particle, physics);

            scene.SetTimer(particle, timer);
        }
    }
}

void Particles::Explosion(Scene &scene, int id)
{
    Transform transform = scene.GetTransform(id);
    Model model = scene.GetModel(id);
    model.mesh.SetMesh(Meshes::ICOSPHERE);
    model.lighting = Lighting::SHADOW;
    Physics physics = scene.GetPhysics(id);
    Timer timer = scene.GetTimer(id);
    timer.start = scene.GetTime();

    for (int i = 0; i < 100; i++)
    {
        int particle = GetSize();

        if (Activate(particle))
        {
            scene.SetModel(particle, model);

            float scale = Utils::RandomFloat(0.0f, 0.1f);
            transform.scaling = Vector3(scale, scale, scale);
            transform.rotation.x = Utils::RandomFloat(0.0f, 360.0f);
            transform.rotation.y = Utils::RandomFloat(0.0f, 360.0f);
            transform.rotation.z = Utils::RandomFloat(0.0f, 360.0f);
            scene.SetTransform(particle, transform);

            physics.velocity.x = Utils::RandomFloat(-10.0f, 10.0f);
            physics.velocity.y = Utils::RandomFloat(-10.0f, 10.0f);
            physics.velocity.z = Utils::RandomFloat(-10.0f, 10.0f);
            scene.SetPhysics(particle, physics);

            scene.SetTimer(particle, timer);
        }
    }
}