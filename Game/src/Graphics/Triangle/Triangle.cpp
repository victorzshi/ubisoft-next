#include "stdafx.h"

#include "Triangle.h"

Triangle::Triangle() : point{Vector3()}
{
}

void Triangle::Render()
{
    for (int i = 0; i < 3; i++)
    {
        int a = i;
        int b = (i + 1) % 3;
        float sx = point[a].x;
        float sy = point[a].y;
        float ex = point[b].x;
        float ey = point[b].y;
        App::DrawLine(sx, sy, ex, ey);
    }
}