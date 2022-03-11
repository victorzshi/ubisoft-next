#include "stdafx.h"

#include "Particles.h"

#include "Math/Random/Random.h"
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

void Particles::CreateExplosion(Scene &scene, Vector3 &position)
{
    for (int i = 0; i < 5; i++)
    {
        int id = GetSize();

        if (Activate(id))
        {
            Model model = scene.GetModel(id);
            model.mesh.SetMesh(Meshes::SPHERE);
            model.color.SetColor(Colors::RANDOM);
            scene.SetModel(id, model);

            float scale = Random::GetFloat(0.0f, 0.1f);

            Transform transform = scene.GetTransform(id);
            transform.position = position;
            transform.scaling = Vector3(scale, scale, scale);
            transform.rotation.x = Random::GetFloat(0.0f, 360.0f);
            transform.rotation.y = Random::GetFloat(0.0f, 360.0f);
            transform.rotation.z = Random::GetFloat(0.0f, 360.0f);
            scene.SetTransform(id, transform);

            Physics physics = scene.GetPhysics(id);
            physics.velocity.x = Random::GetFloat(-5.0f, 5.0f);
            physics.velocity.y = Random::GetFloat(-5.0f, 5.0f);
            physics.velocity.z = Random::GetFloat(-1.0f, 1.0f);
            scene.SetPhysics(id, physics);

            Timer timer = scene.GetTimer(id);
            timer.start = scene.GetTime();
            scene.SetTimer(id, timer);
        }
    }
}

void Particles::CreateBigExplosion(Scene &scene, Vector3 &position)
{
    for (int i = 0; i < 50; i++)
    {
        int id = GetSize();

        if (Activate(id))
        {
            Model model = scene.GetModel(id);
            model.mesh.SetMesh(Meshes::CONE);
            model.color.SetColor(Colors::RANDOM);
            scene.SetModel(id, model);

            float scale = Random::GetFloat(0.0f, 0.5f);

            Transform transform = scene.GetTransform(id);
            transform.position = position;
            transform.scaling = Vector3(scale, scale, scale);
            transform.rotation.x = Random::GetFloat(0.0f, 360.0f);
            transform.rotation.y = Random::GetFloat(0.0f, 360.0f);
            transform.rotation.z = Random::GetFloat(0.0f, 360.0f);
            scene.SetTransform(id, transform);

            Physics physics = scene.GetPhysics(id);
            physics.velocity.x = Random::GetFloat(-5.0f, 5.0f);
            physics.velocity.y = Random::GetFloat(-5.0f, 5.0f);
            physics.velocity.z = Random::GetFloat(-5.0f, 5.0f);
            scene.SetPhysics(id, physics);

            Timer timer = scene.GetTimer(id);
            timer.start = scene.GetTime();
            scene.SetTimer(id, timer);
        }
    }
}