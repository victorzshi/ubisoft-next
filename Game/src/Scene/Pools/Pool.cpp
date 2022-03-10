#include "stdafx.h"

#include "pool.h"

#include "Scene/Scene.h"

Pool::Pool() : m_scene(nullptr), m_begin(0), m_size(0), m_end(0)
{
}

std::vector<int> Pool::GetIds() const
{
    return m_ids;
}

int Pool::GetBegin() const
{
    return m_begin;
}

int Pool::GetSize() const
{
    return m_size;
}

int Pool::GetEnd() const
{
    return m_end;
}

bool Pool::Activate(int id)
{
    assert(id >= m_size);

    // Do not blow memory up
    if (m_size > m_end)
    {
        return false;
    }

    SwapMemory(id);

    m_size++;

    return true;
}

bool Pool::Deactivate(int id)
{
    assert(id < m_size);

    m_size--;

    SwapMemory(id);

    return true;
}

void Pool::UpdateIds()
{
    assert(m_end != 0);

    m_ids.clear();

    for (int id = m_begin; id < m_size; id++)
    {
        m_ids.push_back(id);
    }
}

Scene *Pool::GetScene() const
{
    return m_scene;
}

void Pool::SetScene(Scene *scene)
{
    m_scene = scene;
}

void Pool::SetBegin(int id)
{
    m_begin = id;
}

void Pool::SetSize(int id)
{
    m_size = id;
}

void Pool::SetEnd(int id)
{
    m_end = id;
}

void Pool::SwapMemory(int id)
{
    assert(m_scene != nullptr);

    if (m_size == id)
    {
        return;
    }

    Model model = m_scene->GetModel(m_size);
    m_scene->SetModel(m_size, m_scene->GetModel(id));
    m_scene->SetModel(id, model);

    Physics physics = m_scene->GetPhysics(m_size);
    m_scene->SetPhysics(m_size, m_scene->GetPhysics(id));
    m_scene->SetPhysics(id, physics);

    Timer timer = m_scene->GetTimer(m_size);
    m_scene->SetTimer(m_size, m_scene->GetTimer(id));
    m_scene->SetTimer(id, timer);

    Transform transform = m_scene->GetTransform(m_size);
    m_scene->SetTransform(m_size, m_scene->GetTransform(id));
    m_scene->SetTransform(id, transform);
}