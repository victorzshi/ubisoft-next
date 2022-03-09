#pragma once

enum class Colors
{
    WHITE,
    GREY,
    BLACK,
    RED,
    YELLOW,
    BLUE,
    ORANGE,
    GREEN,
    PURPLE,
    RANDOM,
};

struct Color
{
    int r, g, b;

    Color();

    void SetColor(Colors color);
};