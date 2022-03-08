#include "stdafx.h"

#include "Face.h"

Face::Face() : vertices(0), vertex{Vector3()}, r(1.0f), g(1.0f), b(1.0f)
{
}

void Face::Render()
{
    for (int i = 0; i < vertices; i++)
    {
        int j = i;
        int k = (i + 1) % vertices;
        float sx = vertex[j].x;
        float sy = vertex[j].y;
        float ex = vertex[k].x;
        float ey = vertex[k].y;
        App::DrawLine(sx, sy, ex, ey, r, g, b);
    }
}