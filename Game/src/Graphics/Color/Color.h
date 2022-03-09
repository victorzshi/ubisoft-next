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

class Color
{
  public:
    int r, g, b;

    Color();

    void SetColor(Colors color);
};