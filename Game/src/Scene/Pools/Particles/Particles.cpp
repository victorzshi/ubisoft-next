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
        Timer timer = scene.GetTimer(id);

        if (timer.Elapsed(current) >= timer.stayAlive)
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
    timer.stayAlive = 0.2f;

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
    model.mesh.SetMesh(Meshes::CUBE);
    model.lighting = Lighting::SHADOW;
    Physics physics = scene.GetPhysics(id);
    Timer timer = scene.GetTimer(id);
    timer.start = scene.GetTime();
    timer.stayAlive = 5.0f;

    for (int i = 0; i < 100; i++)
    {
        int particle = GetSize();

        if (Activate(particle))
        {
            scene.SetModel(particle, model);

            // float scale = Utils::RandomFloat(0.0f, 0.1f);
            //  transform.scaling = Vector3(scale, scale, scale);
            transform.scaling.x = Utils::RandomFloat(0.1f, 0.5f);
            transform.scaling.y = Utils::RandomFloat(0.1f, 0.5f);
            transform.scaling.z = 0.0f;
            transform.rotation.x = Utils::RandomFloat(0.0f, 360.0f);
            transform.rotation.y = Utils::RandomFloat(0.0f, 360.0f);
            transform.rotation.z = Utils::RandomFloat(0.0f, 360.0f);
            scene.SetTransform(particle, transform);

            physics.velocity.x = Utils::RandomFloat(-20.0f, 20.0f);
            physics.velocity.y = Utils::RandomFloat(-20.0f, 20.0f);
            physics.velocity.z = Utils::RandomFloat(-20.0f, 20.0f);
            scene.SetPhysics(particle, physics);

            scene.SetTimer(particle, timer);
        }
    }
}