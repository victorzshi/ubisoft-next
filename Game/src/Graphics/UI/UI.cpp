#include "stdafx.h"

#include "UI.h"

UI::UI() : m_scene(nullptr), m_SCREEN_WIDTH(0.0f), m_SCREEN_HEIGHT(0.0f), m_screen(Screen::START)
{
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
    switch (m_screen)
    {
    case Screen::START:
        if (App::IsKeyPressed(VK_SPACE))
        {
            m_screen = Screen::NONE;
        }
        break;

    case Screen::NONE:
        if (App::IsKeyPressed(VK_ESCAPE))
        {
            m_screen = Screen::PAUSED;
        }
        break;

    case Screen::PAUSED:
        if (App::IsKeyPressed(VK_SPACE))
        {
            m_screen = Screen::NONE;
        }
        break;
    }
}

void UI::Render()
{
    float r = 1.0f;
    float g = 1.0f;
    float b = 1.0f;

    switch (m_screen)
    {
    case Screen::START:
        App::Print(100.0f, m_SCREEN_HEIGHT * 0.80f, "Vanguard Mission Zero: Genesis Odyssey", r, g, b, m_FONT);
        App::Print(100.0f, m_SCREEN_HEIGHT * 0.60f, "Controls: WASD to move, LEFT CLICK to fire", r, g, b, m_FONT);
        App::Print(100.0f, m_SCREEN_HEIGHT * 0.40f, "Objective: Eliminate all hostiles", r, g, b, m_FONT);
        App::Print(100.0f, m_SCREEN_HEIGHT * 0.20f, "Press SPACE to start", r, g, b, m_FONT);
        break;

    case Screen::NONE:
        // TODO: Ship UI
        break;

    case Screen::PAUSED:
        App::Print(100.0f, m_SCREEN_HEIGHT * 0.80f, "PAUSED", r, g, b, m_FONT);
        // App::Print(100.0f, m_SCREEN_HEIGHT * 0.60f, "Press H to hide text", r, g, b, m_FONT);
        // App::Print(100.0f, m_SCREEN_HEIGHT * 0.40f, "Press R to restart", r, g, b, m_FONT);
        App::Print(100.0f, m_SCREEN_HEIGHT * 0.20f, "Press SPACE to continue", r, g, b, m_FONT);
        break;
    }
}