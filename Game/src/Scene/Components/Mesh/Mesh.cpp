#include "stdafx.h"

#include "Mesh.h"

#include <fstream>
#include <iostream>
#include <strstream>

Mesh::Mesh()
{
}

Mesh Mesh::LoadFromObjectFile(std::string file)
{
    std::string path = "data/objects/" + file;

    std::ifstream ifs(path);
    assert(ifs.is_open());

    Mesh mesh;
    std::vector<Vector3> vertices;

    while (ifs.good())
    {
        char line[64];
        ifs.getline(line, 64);

        std::strstream s;
        s << line;

        char c;
        if (line[0] == 'v')
        {
            float vertex[3] = {0.0f};
            s >> c >> vertex[0] >> vertex[1] >> vertex[2];

            Vector3 v;
            v.x = vertex[0];
            v.y = vertex[1];
            v.z = vertex[2];
            vertices.push_back(v);
        }
        else if (line[0] == 'f')
        {
            size_t face[3] = {0};
            s >> c >> face[0] >> face[1] >> face[2];

            Triangle triangle;
            triangle.point[0] = vertices[face[0] - 1];
            triangle.point[1] = vertices[face[1] - 1];
            triangle.point[2] = vertices[face[2] - 1];
            mesh.triangles.push_back(triangle);
        }
    }

    return mesh;
}
