#include "stdafx.h"

#include "Scene.h"

#include "Systems/Systems.h"

Scene::Scene() : m_id(0)
{
    m_mesh = new Mesh[MAX_OBJECTS];
    m_physics = new Physics[MAX_OBJECTS];
    m_transform = new Transform[MAX_OBJECTS];
}

void Scene::Init()
{
    SetViewport();
    SetCamera();
    SetWorldMatrix();
    SetViewMatrix();
    SetProjectionMatrix();

    m_asteroids.Init(*this);
    m_grid.Init(*this);
}

void Scene::Shutdown()
{
    delete[] m_mesh;
    delete[] m_physics;
    delete[] m_transform;
    m_mesh = nullptr;
    m_physics = nullptr;
    m_transform = nullptr;
}

Mesh Scene::GetMesh(int id) const
{
    Mesh mesh = m_mesh[id];
    return mesh;
}

Physics Scene::GetPhysics(int id) const
{
    Physics physics = m_physics[id];
    return physics;
}

Transform Scene::GetTransform(int id) const
{
    Transform transform = m_transform[id];
    return transform;
}

void Scene::SetMesh(int id, Mesh mesh)
{
    m_mesh[id] = mesh;
}

void Scene::SetPhysics(int id, Physics physics)
{
    m_physics[id] = physics;
}

void Scene::SetTransform(int id, Transform transform)
{
    m_transform[id] = transform;
}

int Scene::CreateId()
{
    assert(m_id < MAX_OBJECTS);
    m_id++;
    return m_id - 1; // Array index starts at 0
}

void Scene::Update(float deltaTime)
{
    HandleInput();

    std::vector<int> ids = m_asteroids.GetIds();
    for (auto id : ids)
    {
        Systems::UpdatePosition(*this, id, deltaTime);
        Systems::UpdateRotation(*this, id, deltaTime);
    }

    SetViewMatrix();
    UpdateTriangles();
}

void Scene::Render()
{
#ifdef _DEBUG
    RenderBorder();
    // TODO: Draw grid for visualizing 3D space
#endif
    RenderTriangles();
}

void Scene::SetViewport()
{
    m_viewport.x = 0.0f;
    m_viewport.y = 0.0f;
    m_viewport.w = 960.0f;
    m_viewport.h = 540.0f;
}

void Scene::SetCamera()
{
    m_camera.position = Vector3(0.0f, 0.0f, 0.0f);
    m_camera.facing = Vector3(0.0f, 0.0f, 1.0f);
    m_camera.up = Vector3(0.0f, 1.0f, 0.0f);
    m_camera.rotation = Vector3(0.0f, 0.0f, 0.0f);
}

void Scene::SetWorldMatrix()
{
    Matrix scale = Matrix::Scale(Vector3(1.0f, 1.0f, 1.0f));
    Matrix rotate = Matrix::Identity();
    Matrix translate = Matrix::Translate(Vector3(0.0f, 0.0f, 20.0f));
    m_world = scale * rotate * translate;
}

void Scene::SetViewMatrix()
{
    Vector3 direction = Matrix::Rotate(m_camera.rotation) * m_camera.facing;
    Vector3 from = m_camera.position;
    Vector3 to = m_camera.position + direction;
    Vector3 up = m_camera.up;
    m_view = Matrix::LookAt(from, to, up);
}

void Scene::SetProjectionMatrix()
{
    float fov = 90.0f;
    float aspectRatio = m_viewport.w / m_viewport.h;
    float zNear = 0.1f;
    float zFar = 100.0f;
    m_projection = Matrix::Perspective(fov, aspectRatio, zNear, zFar);
}

void Scene::HandleInput()
{
    if (App::GetController().GetLeftThumbStickX() > 0.5f)
    {
        m_camera.position.x += 0.05f;
    }
    if (App::GetController().GetLeftThumbStickX() < -0.5f)
    {
        m_camera.position.x -= 0.05f;
    }
    if (App::GetController().GetLeftThumbStickY() > 0.5f)
    {
        m_camera.position.z -= 0.05f;
    }
    if (App::GetController().GetLeftThumbStickY() < -0.5f)
    {
        m_camera.position.z += 0.05f;
    }
    if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_UP, false))
    {
        m_camera.rotation.x -= 0.5f;
    }
    if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_DOWN, false))
    {
        m_camera.rotation.x += 0.5f;
    }
    if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_RIGHT, false))
    {
        m_camera.rotation.y -= 0.5f;
    }
    if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_LEFT, false))
    {
        m_camera.rotation.y += 0.5f;
    }
}

void Scene::UpdateTriangles()
{
    m_triangles.clear();

    std::vector<int> ids;
    for (auto &id : m_asteroids.GetIds())
    {
        ids.push_back(id);
    }
    for (auto &id : m_grid.GetIds())
    {
        ids.push_back(id);
    }

    for (auto &id : ids)
    {
        Mesh mesh = GetMesh(id);

        // Early exit
        if (mesh.triangles.empty())
        {
            return;
        }

        // Apply local transform
        Transform transform = GetTransform(id);
        Matrix translate = Matrix::Translate(transform.position);
        Matrix rotate = Matrix::Rotate(transform.rotation);
        Matrix scale = Matrix::Scale(transform.scaling);
        Matrix local = scale * rotate * translate;
        for (auto &triangle : mesh.triangles)
        {
            for (int i = 0; i < 3; i++)
            {
                triangle.point[i] = local * triangle.point[i];
            }
        }

        for (auto &triangle : mesh.triangles)
        {
            Triangle transformed;

            // World transform
            for (int i = 0; i < 3; i++)
            {
                transformed.point[i] = m_world * triangle.point[i];
            }

            // Backface culling
            Vector3 a = transformed.point[1] - transformed.point[0];
            Vector3 b = transformed.point[2] - transformed.point[0];
            Vector3 normal = a.Cross(b).Normalize();

            if (normal.Dot((transformed.point[0] - m_camera.position).Normalize()) < 0.0f)
            {
                // Convert world space to view space
                for (int i = 0; i < 3; i++)
                {
                    transformed.point[i] = m_view * transformed.point[i];
                }

                // Project from 3D to 2D
                for (int i = 0; i < 3; i++)
                {
                    transformed.point[i] = m_projection * transformed.point[i];
                }

                // Normalize with reciprocal divide
                for (int i = 0; i < 3; i++)
                {
                    float w = transformed.point[i].w;
                    assert(w != 0.0f);
                    transformed.point[i] /= w;
                }

                // Offset into normalized space
                for (int i = 0; i < 3; i++)
                {
                    transformed.point[i] += Vector3(1.0f, 1.0f, 0.0f);
                    transformed.point[i].x *= m_viewport.w * 0.5f;
                    transformed.point[i].y *= m_viewport.h * 0.5f;
                }

                m_triangles.push_back(transformed);
            }
        }
    }
}

void Scene::RenderTriangles()
{
    for (auto &triangle : m_triangles)
    {
        triangle.Render();
    }
}

void Scene::RenderBorder()
{
    float r = 0.0f;
    float g = 1.0f;
    float b = 0.0f;
    float x = m_viewport.x + 1.0f; // Offset into visible area
    float y = m_viewport.y;
    float w = m_viewport.w;
    float h = m_viewport.h - 1.0f; // Offset into visible area
    App::DrawLine(x, y, x, h, r, g, b);
    App::DrawLine(x, h, w, h, r, g, b);
    App::DrawLine(w, h, w, y, r, g, b);
    App::DrawLine(w, y, x, y, r, g, b);
}