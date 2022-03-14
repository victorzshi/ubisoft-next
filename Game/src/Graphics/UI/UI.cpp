#include "stdafx.h"

#include "UI.h"

#include "Scene/Scene.h"

UI::UI() : m_scene(nullptr), m_SCREEN_WIDTH(0.0f), m_SCREEN_HEIGHT(0.0f), m_screen(Screen::START), m_isHidden(false)
{
    m_pressed = std::chrono::steady_clock::now();
    m_current = m_pressed;
    m_time = m_current - m_pressed;
}

void UI::Init(Scene *scene, float SCREEN_WIDTH, float SCREEN_HEIGHT)
{
    m_scene = scene;
    m_SCREEN_WIDTH = SCREEN_WIDTH;
    m_SCREEN_HEIGHT = SCREEN_HEIGHT;
}

Screen UI::GetScreen() const
{
    return m_screen;
}

void UI::SetScreen(Screen screen)
{
    m_screen = screen;
}

void UI::HandleInput()
{
    m_current = std::chrono::steady_clock::now();
    m_time = m_current - m_pressed;

    switch (m_screen)
    {
    case Screen::START:
        if (App::IsKeyPressed(VK_SPACE))
        {
            m_screen = Screen::NONE;
        }
        break;

    case Screen::NONE:
        if (App::IsKeyPressed(VK_ESCAPE) && m_time.count() > 0.3f)
        {
            m_screen = Screen::PAUSED;
            m_pressed = std::chrono::steady_clock::now();
        }
        break;

    case Screen::PAUSED:
        if (App::IsKeyPressed(VK_ESCAPE) && m_time.count() > 0.3f)
        {
            m_screen = Screen::NONE;
            m_pressed = std::chrono::steady_clock::now();
        }
        if (App::IsKeyPressed('H') && m_time.count() > 0.3f)
        {
            m_isHidden = !m_isHidden;
            m_pressed = std::chrono::steady_clock::now();
        }
        break;
    }
}

void UI::Update()
{
    std::vector<int> ids = m_scene->GetShips().GetIds();

    if (!ids.empty())
    {
        int ship = ids.front();

        Health health = m_scene->GetHealth(ship);
        Timer timer = m_scene->GetTimer(ship);

        int life = health.points;
        int fuel = (int)roundf(timer.stayAlive);

        m_colorLife = GetTextColor(life);
        m_colorFuel = GetTextColor(fuel);

        m_life = "LIFE " + std::string(health.points, '|');
        m_fuel = "FUEL " + std::string(fuel, '|');
    }
    else
    {
        int life = 0;

        m_colorLife = GetTextColor(life);

        m_life = "LIFE " + std::string(life, '|');
    }
}

void UI::Render()
{
    if (m_isHidden)
    {
        return;
    }

    float margin = 100.0f;
    float r = 1.0f;
    float g = 1.0f;
    float b = 1.0f;

    switch (m_screen)
    {
    case Screen::START:
        App::Print(margin, m_SCREEN_HEIGHT * 0.80f, "Vanguard Mission Zero: Genesis Odyssey", r, g, b, m_FONT);
        App::Print(margin, m_SCREEN_HEIGHT * 0.60f, "Controls: WASD to move, LEFT CLICK to fire", r, g, b, m_FONT);
        App::Print(margin, m_SCREEN_HEIGHT * 0.40f, "Objective: Eliminate all hostiles", r, g, b, m_FONT);
        App::Print(margin, m_SCREEN_HEIGHT * 0.20f, "Press SPACE to start", r, g, b, m_FONT);
        break;

    case Screen::NONE:
        PrintShipStats();
        break;

    case Screen::PAUSED:
        App::Print(margin, m_SCREEN_HEIGHT * 0.80f, "PAUSED", r, g, b, m_FONT);
        App::Print(margin, m_SCREEN_HEIGHT * 0.60f, "Press H to hide text", r, g, b, m_FONT);
        // App::Print(margin, m_SCREEN_HEIGHT * 0.40f, "Press R to restart", r, g, b, m_FONT);
        App::Print(margin, m_SCREEN_HEIGHT * 0.20f, "Press ESC to continue", r, g, b, m_FONT);
        PrintShipStats();
        break;
    }
}

Color UI::GetTextColor(int level)
{
    Color color;
    if (level >= 75)
    {
        color.SetColor(Colors::WHITE);
    }
    else if (level >= 50)
    {
        color.SetColor(Colors::YELLOW);
    }
    else if (level >= 25)
    {
        color.SetColor(Colors::ORANGE);
    }
    else
    {
        color.SetColor(Colors::RED);
    }
    return color;
}

void UI::PrintShipStats()
{
    float r = m_colorLife.r / 255.0f;
    float g = m_colorLife.g / 255.0f;
    float b = m_colorLife.b / 255.0f;
    App::Print(10.0f, 30.0f, m_life.c_str(), r, g, b, m_FONT);

    r = m_colorFuel.r / 255.0f;
    g = m_colorFuel.g / 255.0f;
    b = m_colorFuel.b / 255.0f;
    App::Print(10.0f, 10.0f, m_fuel.c_str(), r, g, b, m_FONT);
}