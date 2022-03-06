#include "stdafx.h"

#include "pool.h"

#include "Scene/Scene.h"

Pool::Pool() : m_scene(nullptr), m_begin(0), m_size(0), m_end(0)
{
}

std::vector<int> Pool::GetIds()
{
    assert(m_end != 0);

    std::vector<int> ids;

    for (int id = m_begin; id < m_size; id++)
    {
        ids.push_back(id);
    }

    return ids;
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

    Mesh mesh = m_scene->GetMesh(m_size);
    m_scene->SetMesh(m_size, m_scene->GetMesh(id));
    m_scene->SetMesh(id, mesh);

    Transform transform = m_scene->GetTransform(m_size);
    m_scene->SetTransform(m_size, m_scene->GetTransform(id));
    m_scene->SetTransform(id, transform);
}