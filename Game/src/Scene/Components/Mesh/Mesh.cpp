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
            float v[3] = {0.0f};
            s >> c >> v[0] >> v[1] >> v[2];

            Vector3 vertex;
            vertex.x = v[0];
            vertex.y = v[1];
            vertex.z = v[2];
            vertices.push_back(vertex);
        }
        else if (line[0] == 'f')
        {
            size_t f[4] = {0};
            s >> c >> f[0] >> f[1] >> f[2] >> f[3];

            Face face;
            if (f[3] == 0)
            {
                face.vertices = 3;
                face.vertex[0] = vertices[f[0] - 1];
                face.vertex[1] = vertices[f[1] - 1];
                face.vertex[2] = vertices[f[2] - 1];
            }
            else
            {
                face.vertices = 4;
                face.vertex[0] = vertices[f[0] - 1];
                face.vertex[1] = vertices[f[1] - 1];
                face.vertex[2] = vertices[f[2] - 1];
                face.vertex[3] = vertices[f[3] - 1];
            }
            mesh.faces.push_back(face);
        }
    }

    return mesh;
}
