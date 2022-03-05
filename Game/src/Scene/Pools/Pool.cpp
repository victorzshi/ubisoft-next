#include "stdafx.h"

#include "pool.h"

#include <assert.h>

#include "Scene/Components/Mesh/Mesh.h"
#include "Scene/Components/Transform/Transform.h"
#include "Scene/Scene.h"

Pool::Pool() : m_scene(nullptr), m_begin(0), m_size(0), m_end(0)
{
}

std::vector<size_t> Pool::GetActiveEntities()
{
    assert(m_end != 0);

    std::vector<size_t> active;

    for (size_t id = m_begin; id < m_size; id++)
    {
        active.push_back(id);
    }

    return active;
}

bool Pool::Activate(int index)
{
    assert(index >= m_size);

    // Do not blow memory up
    if (m_size > m_end)
    {
        return false;
    }

    MemorySwap(index);

    m_size++;

    return true;
}

bool Pool::Deactivate(int index)
{
    assert(index < m_size);

    m_size--;

    MemorySwap(index);

    return true;
}

void Pool::SetScene(Scene *scene)
{
    m_scene = scene;
}

void Pool::SetBegin(size_t index)
{
    m_begin = index;
}

void Pool::SetSize(size_t index)
{
    m_size = index;
}

void Pool::SetEnd(size_t index)
{
    m_end = index;
}

void Pool::MemorySwap(int index)
{
    assert(m_scene != nullptr);

    if (m_size == index)
    {
        return;
    }

    Mesh *meshes = m_scene->GetMeshes();
    Transform *transforms = m_scene->GetTransforms();

    Mesh mesh = meshes[m_size];
    meshes[m_size] = meshes[index];
    meshes[index] = mesh;

    Transform transform = transforms[m_size];
    transforms[m_size] = transforms[index];
    transforms[index] = transform;
}