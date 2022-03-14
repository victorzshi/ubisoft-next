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

            float scale = Utils::RandomFloat(0.0f, transform.scaling.x * 0.5f);
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

void Particles::Explode(Scene &scene, int id)
{
    Meshes mesh = scene.GetModel(id).mesh.GetMesh();
    if (mesh == Meshes::CONE)
    {
        App::PlaySound("data/sounds/Explosion3__003.wav");
    }
    else if (mesh == Meshes::MONKEY)
    {
        App::PlaySound("data/sounds/Explosion1__002.wav");
    }
    else if (mesh == Meshes::ICOSPHERE) 
    {
        App::PlaySound("data/sounds/Explosion2__004.wav");
    }
    else if (mesh == Meshes::TORUS)
    {
        App::PlaySound("data/sounds/Explosion2__006.wav");
    }
    else if (mesh == Meshes::CUBE)
    {
        App::PlaySound("data/sounds/Pickup__008.wav");
    }

    // Explosion of lines
    Model model = scene.GetModel(id);
    model.mesh.SetMesh(Meshes::TWOPLANE);
    model.lighting = Lighting::SHADOW;

    Transform transform = scene.GetTransform(id);
    transform.scaling.x = transform.scaling.x * 0.01f;
    transform.scaling.y = transform.scaling.y * 0.01f;
    transform.scaling.z = transform.scaling.z * 1.0f;

    Physics physics = scene.GetPhysics(id);

    Timer timer = scene.GetTimer(id);
    timer.start = scene.GetTime();
    timer.stayAlive = 3.0f;

    for (int i = 0; i < 100; i++)
    {
        int particle = GetSize();

        if (Activate(particle))
        {
            scene.SetModel(particle, model);

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

void Particles::Boost(Scene &scene, int id, Vector3 &direction)
{
    Meshes mesh = scene.GetModel(id).mesh.GetMesh();
    if (mesh == Meshes::CONE && !App::IsSoundPlaying("data/sounds/Bass Drum__004.wav"))
    {
        App::PlaySound("data/sounds/Bass Drum__004.wav");
    }

    Transform transform = scene.GetTransform(id);
    transform.position += direction * -transform.scaling.x * 0.5f;
    transform.scaling = Vector3(0.1f, 0.1f, 0.1f);

    Model model = scene.GetModel(id);
    model.mesh.SetMesh(Meshes::CONE);
    model.color.SetColor(Colors::ORANGE);
    model.lighting = Lighting::BRIGHT;

    Physics physics = scene.GetPhysics(id);

    Timer timer = scene.GetTimer(id);
    timer.start = scene.GetTime();
    timer.stayAlive = 0.3f;

    for (int i = 0; i < 5; i++)
    {
        int particle = GetSize();

        if (Activate(particle))
        {
            scene.SetTransform(particle, transform);

            scene.SetModel(particle, model);

            physics.velocity.x = Utils::RandomFloat(-1.0f, 1.0f);
            physics.velocity.y = Utils::RandomFloat(-1.0f, 1.0f);
            physics.velocity.z = Utils::RandomFloat(-1.0f, 1.0f);
            scene.SetPhysics(particle, physics);

            scene.SetTimer(particle, timer);
        }
    }
}