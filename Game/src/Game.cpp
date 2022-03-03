#include "stdafx.h"

#include <math.h>
#include <windows.h>

#include "..\external\App\app.h"

CSimpleSprite *testSprite;
enum
{
    ANIM_FORWARDS,
    ANIM_BACKWARDS,
    ANIM_LEFT,
    ANIM_RIGHT,
};

void Init()
{
    testSprite = App::CreateSprite("data/Test.bmp", 8, 4);
    testSprite->SetPosition(400.0f, 400.0f);
    float speed = 1.0f / 15.0f;
    testSprite->CreateAnimation(ANIM_BACKWARDS, speed, {0, 1, 2, 3, 4, 5, 6, 7});
    testSprite->CreateAnimation(ANIM_LEFT, speed, {8, 9, 10, 11, 12, 13, 14, 15});
    testSprite->CreateAnimation(ANIM_RIGHT, speed, {16, 17, 18, 19, 20, 21, 22, 23});
    testSprite->CreateAnimation(ANIM_FORWARDS, speed, {24, 25, 26, 27, 28, 29, 30, 31});
    testSprite->SetScale(2.0f);
}

void Update(float deltaTime)
{
    testSprite->Update(deltaTime);
    if (App::GetController().GetLeftThumbStickX() > 0.5f)
    {
        testSprite->SetAnimation(ANIM_RIGHT);
        float x, y;
        testSprite->GetPosition(x, y);
        x += 1.0f;
        testSprite->SetPosition(x, y);
    }
    if (App::GetController().GetLeftThumbStickX() < -0.5f)
    {
        testSprite->SetAnimation(ANIM_LEFT);
        float x, y;
        testSprite->GetPosition(x, y);
        x -= 1.0f;
        testSprite->SetPosition(x, y);
    }
    if (App::GetController().GetLeftThumbStickY() > 0.5f)
    {
        testSprite->SetAnimation(ANIM_FORWARDS);
        float x, y;
        testSprite->GetPosition(x, y);
        y += 1.0f;
        testSprite->SetPosition(x, y);
    }
    if (App::GetController().GetLeftThumbStickY() < -0.5f)
    {
        testSprite->SetAnimation(ANIM_BACKWARDS);
        float x, y;
        testSprite->GetPosition(x, y);
        y -= 1.0f;
        testSprite->SetPosition(x, y);
    }
    if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_UP, false))
    {
        testSprite->SetScale(testSprite->GetScale() + 0.1f);
    }
    if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_DOWN, false))
    {
        testSprite->SetScale(testSprite->GetScale() - 0.1f);
    }
    if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_LEFT, false))
    {
        testSprite->SetAngle(testSprite->GetAngle() + 0.1f);
    }
    if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_RIGHT, false))
    {
        testSprite->SetAngle(testSprite->GetAngle() - 0.1f);
    }
    if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
    {
        testSprite->SetAnimation(-1);
    }
    if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
    {
        App::PlaySound("data/Test.wav");
    }
}

void Render()
{
    testSprite->Draw();

    App::Print(100, 100, "Sample Text");

    static float a = 0.0f;
    float r = 1.0f;
    float g = 1.0f;
    float b = 1.0f;
    a += 0.1f;
    for (int i = 0; i < 20; i++)
    {
        float sx = 200 + sinf(a + i * 0.1f) * 60.0f;
        float sy = 200 + cosf(a + i * 0.1f) * 60.0f;
        float ex = 700 - sinf(a + i * 0.1f) * 60.0f;
        float ey = 700 - cosf(a + i * 0.1f) * 60.0f;
        g = (float)i / 20.0f;
        b = (float)i / 20.0f;
        App::DrawLine(sx, sy, ex, ey, r, g, b);
    }
}

void Shutdown()
{
    delete testSprite;
}