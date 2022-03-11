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

        Model model;
        model.lighting = Lighting::OUTLINE;
        scene.SetModel(id, model);

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

void Particles::CreateExplosion(Scene &scene, int id)
{
    Vector3 position = scene.GetTransform(id).position;

    for (int i = 0; i < 5; i++)
    {
        int particle = GetSize();

        if (Activate(particle))
        {
            Model model = scene.GetModel(particle);
            model.mesh.SetMesh(Meshes::SPHERE);
            model.color.SetColor(Colors::RANDOM);
            scene.SetModel(particle, model);

            float scale = Utils::RandomFloat(0.0f, 0.1f);

            Transform transform = scene.GetTransform(particle);
            transform.position = position;
            transform.scaling = Vector3(scale, scale, scale);
            transform.rotation.x = Utils::RandomFloat(0.0f, 360.0f);
            transform.rotation.y = Utils::RandomFloat(0.0f, 360.0f);
            transform.rotation.z = Utils::RandomFloat(0.0f, 360.0f);
            scene.SetTransform(particle, transform);

            Physics physics = scene.GetPhysics(particle);
            physics.velocity.x = Utils::RandomFloat(-5.0f, 5.0f);
            physics.velocity.y = Utils::RandomFloat(-5.0f, 5.0f);
            physics.velocity.z = Utils::RandomFloat(-1.0f, 1.0f);
            scene.SetPhysics(particle, physics);

            Timer timer = scene.GetTimer(particle);
            timer.start = scene.GetTime();
            scene.SetTimer(particle, timer);
        }
    }
}

void Particles::CreateBigExplosion(Scene &scene, int id)
{
    Vector3 position = scene.GetTransform(id).position;

    for (int i = 0; i < 50; i++)
    {
        int particle = GetSize();

        if (Activate(particle))
        {
            Model model = scene.GetModel(particle);
            model.mesh.SetMesh(Meshes::CONE);
            model.color.SetColor(Colors::RANDOM);
            scene.SetModel(particle, model);

            float scale = Utils::RandomFloat(0.0f, 0.5f);

            Transform transform = scene.GetTransform(particle);
            transform.position = position;
            transform.scaling = Vector3(scale, scale, scale);
            transform.rotation.x = Utils::RandomFloat(0.0f, 360.0f);
            transform.rotation.y = Utils::RandomFloat(0.0f, 360.0f);
            transform.rotation.z = Utils::RandomFloat(0.0f, 360.0f);
            scene.SetTransform(particle, transform);

            Physics physics = scene.GetPhysics(particle);
            physics.velocity.x = Utils::RandomFloat(-5.0f, 5.0f);
            physics.velocity.y = Utils::RandomFloat(-5.0f, 5.0f);
            physics.velocity.z = Utils::RandomFloat(-5.0f, 5.0f);
            scene.SetPhysics(particle, physics);

            Timer timer = scene.GetTimer(particle);
            timer.start = scene.GetTime();
            scene.SetTimer(particle, timer);
        }
    }
}