#include "stdafx.h"

#include "Scene.h"

#include "Systems/Systems.h"

Scene::Scene() : m_id(0)
{
}

void Scene::Init()
{
    SetCamera();
    SetWorldMatrix();
    SetViewMatrix();
    SetProjectionMatrix();

    m_asteroids.Init(*this);
    m_grid.Init(*this);
    m_ships.Init(*this);
}

void Scene::Shutdown()
{
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
    m_mesh.push_back(Mesh());
    m_physics.push_back(Physics());
    m_transform.push_back(Transform());

    m_id++;
    return m_id - 1; // Array index starts at 0
}

void Scene::Update(float deltaTime)
{
#ifdef _DEBUG
    MoveCamera(deltaTime);
#endif

    if (App::IsKeyPressed(VK_LBUTTON))
    {
        Vector3 ray = GetPickRay();

        // Intersection with z=0 plane
        float t = -m_camera.from.z / ray.z;
        m_click = m_camera.from + ray * t;
    }

    std::vector<int> ids = m_ships.GetIds();
    for (auto id : ids)
    {
        Systems::MoveShip(*this, id);
        Systems::UpdatePosition(*this, id, deltaTime);
    }

    ids = m_asteroids.GetIds();
    for (auto id : ids)
    {
        Systems::UpdatePosition(*this, id, deltaTime);
        Systems::AddRotation(*this, id, deltaTime);
    }

    // Look at ship
    int id = m_ships.GetIds().front();
    m_camera.to = GetTransform(id).position;

    SetViewMatrix();
    UpdateVisible();
}

void Scene::Render()
{
#ifdef _DEBUG
    RenderBorder();

    std::string text = "Click: " + m_click.ToString();
    App::Print(10.0f, 100.0f, text.c_str());
#endif
    RenderVisible();
}

void Scene::SetCamera()
{
    m_camera.from = Vector3(0.0f, 0.0f, 20.0f);
    m_camera.to = Vector3(0.0f, 0.0f, 1.0f);
    m_camera.up = Vector3(0.0f, 1.0f, 0.0f);
}

void Scene::SetWorldMatrix()
{
    Matrix scale = Matrix::Scale(Vector3(1.0f, 1.0f, 1.0f));
    Matrix rotate = Matrix::Identity();
    Matrix translate = Matrix::Translate(Vector3(0.0f, 0.0f, 0.0f));
    m_world = scale * rotate * translate;
}

void Scene::SetViewMatrix()
{
    // TODO: Set LookAt and PointAt here.
    Vector3 from = m_camera.from;
    Vector3 to = m_camera.to;
    Vector3 up = m_camera.up;
    m_view = Matrix::LookAt(from, to, up);
    m_viewInverse = Matrix::ViewToWorld(from, to, up);
}

void Scene::SetProjectionMatrix()
{
    // Calculate projection here.
    float fov = 90.0f;
    float aspectRatio = m_SCREEN_WIDTH / m_SCREEN_HEIGHT;
    float zNear = 0.1f;
    float zFar = 25.0f;
    m_projection = Matrix::Perspective(fov, aspectRatio, zNear, zFar);
}

Vector3 Scene::GetPickRay()
{
    float x, y;
    App::GetMousePos(x, y);

    float theta = m_FOV * (PI / 180.0f);
    float distance = 1.0f / tanf(theta * 0.5f);
    float aspectRatio = m_SCREEN_WIDTH / m_SCREEN_HEIGHT;

    Vector3 viewPoint;
    viewPoint.x = 2.0f * aspectRatio * x / m_SCREEN_WIDTH - aspectRatio;
    viewPoint.y = -2.0f * y / m_SCREEN_HEIGHT + 1.0f;
    viewPoint.z = -distance;

    Vector3 worldPoint;
    worldPoint.x = m_viewInverse(0, 0) * viewPoint.x + m_viewInverse(0, 1) * viewPoint.y +
                   m_viewInverse(0, 2) * viewPoint.z + m_viewInverse(0, 3);
    worldPoint.y = m_viewInverse(1, 0) * viewPoint.x + m_viewInverse(1, 1) * viewPoint.y +
                   m_viewInverse(1, 2) * viewPoint.z + m_viewInverse(1, 3);
    worldPoint.z = m_viewInverse(2, 0) * viewPoint.x + m_viewInverse(2, 1) * viewPoint.y +
                   m_viewInverse(2, 2) * viewPoint.z + m_viewInverse(2, 3);

    return worldPoint - m_camera.from;
}

void Scene::MoveCamera(float deltaTime)
{
    float deltaVelocity = deltaTime / 100.0f;

    if (App::IsKeyPressed(VK_NUMPAD6))
    {
        m_camera.from.x += deltaVelocity;
    }
    if (App::IsKeyPressed(VK_NUMPAD4))
    {
        m_camera.from.x -= deltaVelocity;
    }
    if (App::IsKeyPressed(VK_NUMPAD8))
    {
        m_camera.from.z -= deltaVelocity;
    }
    if (App::IsKeyPressed(VK_NUMPAD2))
    {
        m_camera.from.z += deltaVelocity;
    }
    if (App::IsKeyPressed(VK_NUMPAD7))
    {
        m_camera.from.y += deltaVelocity;
    }
    if (App::IsKeyPressed(VK_NUMPAD9))
    {
        m_camera.from.y -= deltaVelocity;
    }
}

void Scene::UpdateVisible()
{
    m_triangles.clear();
    m_quads.clear();

    std::vector<int> ids;
    for (auto &id : m_asteroids.GetIds())
    {
        ids.push_back(id);
    }
    for (auto &id : m_grid.GetIds())
    {
        ids.push_back(id);
    }
    for (auto &id : m_ships.GetIds())
    {
        ids.push_back(id);
    }

    for (auto &id : ids)
    {
        Mesh mesh = GetMesh(id);

        // Early exit
        if (mesh.triangles.empty() && mesh.quads.empty())
        {
            return;
        }

        // Calculate local transform
        Transform transform = GetTransform(id);
        Matrix translate = Matrix::Translate(transform.position);
        Matrix rotate = Matrix::Rotate(transform.rotation);
        Matrix scale = Matrix::Scale(transform.scaling);
        Matrix local = scale * rotate * translate;

        for (auto &triangle : mesh.triangles)
        {
            // Apply local transform
            for (int i = 0; i < 3; i++)
            {
                triangle.point[i] = local * triangle.point[i];
            }

            // Apply world transform
            for (int i = 0; i < 3; i++)
            {
                triangle.point[i] = m_world * triangle.point[i];
            }

            // Calculate normal for backface culling
            Vector3 a = triangle.point[1] - triangle.point[0];
            Vector3 b = triangle.point[2] - triangle.point[0];
            Vector3 normal = a.Cross(b).Normalize();

            if (normal.Dot((triangle.point[0] - m_camera.from).Normalize()) < 0.0f)
            {
                // Convert world space to view space
                for (int i = 0; i < 3; i++)
                {
                    triangle.point[i] = m_view * triangle.point[i];
                }

                // Project from 3D to 2D
                for (int i = 0; i < 3; i++)
                {
                    triangle.point[i] = m_projection * triangle.point[i];
                }

                // Normalize with reciprocal divide
                for (int i = 0; i < 3; i++)
                {
                    float w = triangle.point[i].w;
                    if (w != 0.0f)
                    {
                        triangle.point[i] /= w;
                    }
                }

                // Offset into normalized space
                float offsetWidth = m_SCREEN_WIDTH * 0.5f;
                float offsetHeight = m_SCREEN_HEIGHT * 0.5f;
                for (int i = 0; i < 3; i++)
                {
                    triangle.point[i].x = offsetWidth * triangle.point[i].x + offsetWidth;
                    triangle.point[i].y = -offsetHeight * triangle.point[i].y + offsetHeight;
                    triangle.point[i].z = 0.5f * triangle.point[i].z + 0.5f;
                }

                m_triangles.push_back(triangle);
            }
        }

        for (auto &quad : mesh.quads)
        {
            // Apply local transform
            for (int i = 0; i < 4; i++)
            {
                quad.point[i] = local * quad.point[i];
            }

            // Apply world transform
            for (int i = 0; i < 4; i++)
            {
                quad.point[i] = m_world * quad.point[i];
            }

            // Calculate normal for backface culling
            Vector3 a = quad.point[1] - quad.point[0];
            Vector3 b = quad.point[2] - quad.point[0];
            Vector3 normal = a.Cross(b).Normalize();

            if (normal.Dot((quad.point[0] - m_camera.from).Normalize()) < 0.0f)
            {
                // Convert world space to view space
                for (int i = 0; i < 4; i++)
                {
                    quad.point[i] = m_view * quad.point[i];
                }

                // Project from 3D to 2D
                for (int i = 0; i < 4; i++)
                {
                    quad.point[i] = m_projection * quad.point[i];
                }

                // Normalize with reciprocal divide
                for (int i = 0; i < 4; i++)
                {
                    float w = quad.point[i].w;
                    if (w != 0.0f)
                    {
                        quad.point[i] /= w;
                    }
                }

                // Offset into normalized space
                float offsetWidth = m_SCREEN_WIDTH * 0.5f;
                float offsetHeight = m_SCREEN_HEIGHT * 0.5f;
                for (int i = 0; i < 4; i++)
                {
                    quad.point[i].x = offsetWidth * quad.point[i].x + offsetWidth;
                    quad.point[i].y = -offsetHeight * quad.point[i].y + offsetHeight;
                    quad.point[i].z = 0.5f * quad.point[i].z + 0.5f;
                }

                m_quads.push_back(quad);
            }
        }
    }
}

void Scene::RenderVisible()
{
    for (auto &triangle : m_triangles)
    {
        triangle.Render();
    }
    for (auto &quad : m_quads)
    {
        quad.Render();
    }
}

void Scene::RenderBorder()
{
    float r = 0.0f;
    float g = 1.0f;
    float b = 0.0f;
    float x = 1.0f; // Offset into visible area
    float y = 0.0f;
    float w = m_SCREEN_WIDTH;
    float h = m_SCREEN_HEIGHT - 1.0f; // Offset into visible area
    App::DrawLine(x, y, x, h, r, g, b);
    App::DrawLine(x, h, w, h, r, g, b);
    App::DrawLine(w, h, w, y, r, g, b);
    App::DrawLine(w, y, x, y, r, g, b);
}