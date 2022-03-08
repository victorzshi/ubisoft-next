#include "stdafx.h"

#include "Face.h"

Face::Face() : vertices(0), vertex{Vector3()}, color(Color())
{
}

void Face::Render()
{
    for (int i = 0; i < vertices; i++)
    {
        int a = i;
        int b = (i + 1) % vertices;
        float sx = vertex[a].x;
        float sy = vertex[a].y;
        float ex = vertex[b].x;
        float ey = vertex[b].y;
        App::DrawLine(sx, sy, ex, ey, color.r, color.g, color.b);
    }
}