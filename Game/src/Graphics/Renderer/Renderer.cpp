#include "stdafx.h"

#include "Renderer.h"

#include <algorithm>

#include "Scene/Scene.h"

Renderer::Renderer() : m_scene(nullptr)
{
}

void Renderer::Init(Scene &scene)
{
    m_scene = &scene;
    SetWorldMatrix();
    SetViewMatrix();
    SetProjectionMatrix();
}

Vector3 Renderer::GetMousePosition() const
{
    return m_mouse;
}

void Renderer::SetCameraPosition(Vector3 position)
{
    m_camera.from = position;
}

void Renderer::SetCameraTarget(Vector3 target)
{
    m_camera.to = target;
}

void Renderer::MoveCamera(float deltaTime)
{
    Vector3 position = m_camera.from;

    float deltaVelocity = deltaTime / 100.0f;

    if (App::IsKeyPressed('W'))
    {
        position.z -= deltaVelocity;
    }
    if (App::IsKeyPressed('S'))
    {
        position.z += deltaVelocity;
    }
    if (App::IsKeyPressed('A'))
    {
        position.x -= deltaVelocity;
    }
    if (App::IsKeyPressed('D'))
    {
        position.x += deltaVelocity;
    }
    if (App::IsKeyPressed(VK_SPACE))
    {
        position.y -= deltaVelocity;
    }
    if (App::IsKeyPressed(VK_CONTROL))
    {
        position.y += deltaVelocity;
    }

    SetCameraPosition(position);
    Update(deltaTime);
}

void Renderer::Update(float deltaTime)
{
    SetViewMatrix();
    SetMousePosition();
    UpdateVisible();
    SortVisible();
}

void Renderer::Render()
{
    RenderVisible();
#ifdef _DEBUG
    RenderBorder();
#endif
}

void Renderer::SetWorldMatrix()
{
    Matrix scale = Matrix::Scale(Vector3(1.0f, 1.0f, 1.0f));
    Matrix rotate = Matrix::Identity();
    Matrix translate = Matrix::Translate(Vector3(0.0f, 0.0f, 0.0f));
    m_world = scale * rotate * translate;
}

void Renderer::SetViewMatrix()
{
    Vector3 from = m_camera.from;
    Vector3 to = m_camera.to;
    Vector3 up = m_camera.up;

    Vector3 zAxis = (to - from).Normalize();        // Forward
    Vector3 xAxis = zAxis.Cross(up).Normalize();    // Right
    Vector3 yAxis = xAxis.Cross(zAxis).Normalize(); // Up

    zAxis *= -1;

    m_view(0, 0) = xAxis.x;
    m_view(0, 1) = yAxis.x;
    m_view(0, 2) = zAxis.x;
    m_view(0, 3) = 0.0f;
    m_view(1, 0) = xAxis.y;
    m_view(1, 1) = yAxis.y;
    m_view(1, 2) = zAxis.y;
    m_view(1, 3) = 0.0f;
    m_view(2, 0) = xAxis.z;
    m_view(2, 1) = yAxis.z;
    m_view(2, 2) = zAxis.z;
    m_view(2, 3) = 0.0f;
    m_view(3, 0) = -xAxis.Dot(from);
    m_view(3, 1) = -yAxis.Dot(from);
    m_view(3, 2) = -zAxis.Dot(from);
    m_view(3, 3) = 1.0f;

    m_viewInverse(0, 0) = xAxis.x;
    m_viewInverse(0, 1) = xAxis.y;
    m_viewInverse(0, 2) = xAxis.z;
    m_viewInverse(0, 3) = 0.0f;
    m_viewInverse(1, 0) = yAxis.x;
    m_viewInverse(1, 1) = yAxis.y;
    m_viewInverse(1, 2) = yAxis.z;
    m_viewInverse(1, 3) = 0.0f;
    m_viewInverse(2, 0) = zAxis.x;
    m_viewInverse(2, 1) = zAxis.y;
    m_viewInverse(2, 2) = zAxis.z;
    m_viewInverse(2, 3) = 0.0f;
    m_viewInverse(3, 0) = from.x;
    m_viewInverse(3, 1) = from.y;
    m_viewInverse(3, 2) = from.z;
    m_viewInverse(3, 3) = 1.0f;
}

void Renderer::SetProjectionMatrix()
{
    float reciprocal = 1.0f / (m_Z_NEAR - m_Z_FAR);

    m_projection(0, 0) = m_DISTANCE / m_ASPECT_RATIO;
    m_projection(1, 1) = m_DISTANCE;
    m_projection(2, 2) = (m_Z_NEAR + m_Z_FAR) * reciprocal;
    m_projection(2, 3) = 2.0f * m_Z_NEAR * m_Z_FAR * reciprocal;
    m_projection(3, 2) = -1.0f;
    m_projection(3, 3) = 0.0f;
}

void Renderer::SetMousePosition()
{
    float mouseX, mouseY;
    App::GetMousePos(mouseX, mouseY);

    Vector3 viewPoint;
    viewPoint.x = 2.0f * m_ASPECT_RATIO * mouseX / SCREEN_WIDTH - m_ASPECT_RATIO;
    viewPoint.y = -2.0f * mouseY / SCREEN_HEIGHT + 1.0f;
    viewPoint.z = -m_DISTANCE;

    Vector3 worldPoint = m_viewInverse * viewPoint;

    if (worldPoint.w != 0.0f)
    {
        worldPoint /= worldPoint.w;
    }

    Vector3 ray = worldPoint - m_camera.from;

    // Intersection with z=0 plane
    float t = -m_camera.from.z / ray.z;
    m_mouse = m_camera.from + ray * t;
}

void Renderer::UpdateVisible()
{
    m_visible.clear();

    for (auto &id : m_scene->GetAllIds())
    {
        Model model = m_scene->GetModel(id);
        std::vector<Face> faces = model.mesh.GetFaces();

        // Early exit
        if (faces.empty())
        {
            return;
        }

        // Calculate local transform
        Transform transform = m_scene->GetTransform(id);
        Matrix translate = Matrix::Translate(transform.position);
        Matrix rotate = Matrix::Rotate(transform.rotation);
        Matrix scale = Matrix::Scale(transform.scaling);
        Matrix local = scale * rotate * translate;

        for (auto &face : faces)
        {
            // Apply local transform
            for (int i = 0; i < face.vertices; i++)
            {
                face.vertex[i] = local * face.vertex[i];
            }

            // Apply world transform
            for (int i = 0; i < face.vertices; i++)
            {
                face.vertex[i] = m_world * face.vertex[i];
            }

            // Calculate normal for backface culling
            Vector3 a = face.vertex[1] - face.vertex[0];
            Vector3 b = face.vertex[2] - face.vertex[0];
            Vector3 normal = a.Cross(b).Normalize();

            if (normal.Dot((face.vertex[0] - m_camera.from).Normalize()) < 0.0f)
            {
                // Convert world space to view space
                for (int i = 0; i < face.vertices; i++)
                {
                    face.vertex[i] = m_view * face.vertex[i];
                }

                // Project from 3D to 2D
                for (int i = 0; i < face.vertices; i++)
                {
                    face.vertex[i] = m_projection * face.vertex[i];
                }

                Vector3 planePoint = Vector3(0.0f, 0.0f, m_Z_NEAR);
                Vector3 planeNormal = Vector3(0.0f, 0.0f, 1.0f);
                Face clipped = ClipAgainstPlane(planePoint, planeNormal, face);

                if (clipped.vertices > 0)
                {
                    // Normalize with reciprocal divide
                    for (int i = 0; i < clipped.vertices; i++)
                    {
                        float w = clipped.vertex[i].w;
                        if (w != 0.0f)
                        {
                            clipped.vertex[i] /= w;
                        }
                    }

                    // Offset into normalized space
                    float offsetWidth = SCREEN_WIDTH * 0.5f;
                    float offsetHeight = SCREEN_HEIGHT * 0.5f;
                    for (int i = 0; i < clipped.vertices; i++)
                    {
                        clipped.vertex[i].x = offsetWidth * clipped.vertex[i].x + offsetWidth;
                        clipped.vertex[i].y = -offsetHeight * clipped.vertex[i].y + offsetHeight;
                        clipped.vertex[i].z = 0.5f * clipped.vertex[i].z + 0.5f;
                    }

                    // Add lighting effect
                    Vector3 sun;
                    if (model.lighting == Lighting::OUTLINE)
                    {
                        sun = m_camera.from.Normalize();
                    }
                    else
                    {
                        sun = Vector3(0.0f, 0.0f, 1.0f).Normalize();
                    }
                    model.ApplyLighting(normal.Dot(sun), clipped);

                    m_visible.push_back(clipped);
                }
            }
        }
    }
}

void Renderer::SortVisible()
{
    std::sort(m_visible.begin(), m_visible.end(), [](Face &a, Face &b) {
        float z1 = 0.0f;
        float z2 = 0.0f;

        for (int i = 0; i < a.vertices; i++)
        {
            z1 += a.vertex[i].z;
        }
        for (int i = 0; i < b.vertices; i++)
        {
            z2 += b.vertex[i].z;
        }

        z1 /= a.vertices;
        z2 /= b.vertices;

        return z1 > z2;
    });
}

void Renderer::RenderVisible()
{
    for (auto &face : m_visible)
    {
        face.Render();
    }
}

void Renderer::RenderBorder()
{
    float r = 0.0f;
    float g = 1.0f;
    float b = 0.0f;
    float x = 1.0f; // Offset into visible area
    float y = 0.0f;
    float w = SCREEN_WIDTH;
    float h = SCREEN_HEIGHT - 1.0f; // Offset into visible area
    App::DrawLine(x, y, x, h, r, g, b);
    App::DrawLine(x, h, w, h, r, g, b);
    App::DrawLine(w, h, w, y, r, g, b);
    App::DrawLine(w, y, x, y, r, g, b);
}

Face Renderer::ClipAgainstPlane(Vector3 &point, Vector3 &normal, Face &face) const
{
    Face clipped;

    // If shortest distance from vertex to plane is positive, vertex lies on inside of plane
    int count = 0;
    float dot = normal.Dot(point);
    for (int i = 0; i < face.vertices; i++)
    {
        Vector3 vertex = face.vertex[i];
        float distance = normal.x * vertex.x + normal.y * vertex.y + normal.z * vertex.z - dot;
        if (distance >= 0)
        {
            count++;
        }
    }

    // Only keep faces that are fully in view
    if (count == face.vertices)
    {
        clipped = face;
    }

    return clipped;
}