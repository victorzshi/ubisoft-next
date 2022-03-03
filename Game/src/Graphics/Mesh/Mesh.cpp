#include "stdafx.h"

#include "Mesh.h"

Mesh Mesh::Cube()
{
    Mesh mesh;

    Vector3 p1 = Vector3(0.0f, 0.0f, 0.0f);
    Vector3 p2 = Vector3(0.0f, 1.0f, 0.0f);
    Vector3 p3 = Vector3(1.0f, 1.0f, 0.0f);
    mesh.triangles.push_back(Triangle(p1, p2, p3));
    p1 = Vector3(0.0f, 0.0f, 0.0f);
    p2 = Vector3(1.0f, 1.0f, 0.0f);
    p3 = Vector3(1.0f, 0.0f, 0.0f);
    mesh.triangles.push_back(Triangle(p1, p2, p3));

    p1 = Vector3(1.0f, 0.0f, 0.0f);
    p2 = Vector3(1.0f, 1.0f, 0.0f);
    p3 = Vector3(1.0f, 1.0f, 1.0f);
    mesh.triangles.push_back(Triangle(p1, p2, p3));
    p1 = Vector3(1.0f, 0.0f, 0.0f);
    p2 = Vector3(1.0f, 1.0f, 1.0f);
    p3 = Vector3(1.0f, 0.0f, 1.0f);
    mesh.triangles.push_back(Triangle(p1, p2, p3));

    p1 = Vector3(1.0f, 0.0f, 1.0f);
    p2 = Vector3(1.0f, 1.0f, 1.0f);
    p3 = Vector3(0.0f, 1.0f, 1.0f);
    mesh.triangles.push_back(Triangle(p1, p2, p3));
    p1 = Vector3(1.0f, 0.0f, 1.0f);
    p2 = Vector3(0.0f, 1.0f, 1.0f);
    p3 = Vector3(0.0f, 0.0f, 1.0f);
    mesh.triangles.push_back(Triangle(p1, p2, p3));

    p1 = Vector3(0.0f, 0.0f, 1.0f);
    p2 = Vector3(0.0f, 1.0f, 1.0f);
    p3 = Vector3(0.0f, 1.0f, 0.0f);
    mesh.triangles.push_back(Triangle(p1, p2, p3));
    p1 = Vector3(0.0f, 0.0f, 1.0f);
    p2 = Vector3(0.0f, 1.0f, 0.0f);
    p3 = Vector3(0.0f, 0.0f, 0.0f);
    mesh.triangles.push_back(Triangle(p1, p2, p3));

    p1 = Vector3(0.0f, 1.0f, 0.0f);
    p2 = Vector3(0.0f, 1.0f, 1.0f);
    p3 = Vector3(1.0f, 1.0f, 1.0f);
    mesh.triangles.push_back(Triangle(p1, p2, p3));
    p1 = Vector3(0.0f, 1.0f, 0.0f);
    p2 = Vector3(1.0f, 1.0f, 1.0f);
    p3 = Vector3(1.0f, 1.0f, 0.0f);
    mesh.triangles.push_back(Triangle(p1, p2, p3));

    p1 = Vector3(1.0f, 0.0f, 1.0f);
    p2 = Vector3(0.0f, 0.0f, 1.0f);
    p3 = Vector3(0.0f, 0.0f, 0.0f);
    mesh.triangles.push_back(Triangle(p1, p2, p3));
    p1 = Vector3(1.0f, 0.0f, 1.0f);
    p2 = Vector3(0.0f, 0.0f, 0.0f);
    p3 = Vector3(1.0f, 0.0f, 0.0f);
    mesh.triangles.push_back(Triangle(p1, p2, p3));

    return mesh;
}