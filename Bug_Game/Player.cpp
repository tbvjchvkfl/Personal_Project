#include "Player.h"


Player::Player(D2DFramework* pFramework) : Actor(pFramework, L"Images/Player.png")
{
    RECT rct;
    GetClientRect(pFramework->GetHWND(), &rct);

    mX = (rct.right + rct.left) / 2.0f;
    mY = (rct.bottom + rct.top) / 2.0f;

    mSpeed = 1.0f;
    mVelocity = 1.0f;
}

Player::~Player()
{
}

void Player::Draw()
{
    ID2D1HwndRenderTarget* pRenderTarget = mpFramework->GetRenderTarget();
    if (!pRenderTarget)
    {
        return;
    }

    input();

    D2D1_SIZE_U size = mpBitmap->GetPixelSize();

    auto matTranslate = D2D1::Matrix3x2F::Translation(mX, mY);
    pRenderTarget->SetTransform(matTranslate);

    D2D1_RECT_F rect{ 0,0,static_cast<float>(size.width), static_cast<float>(size.height) };
    pRenderTarget->DrawBitmap(mpBitmap, rect, mOpacity);
}

bool Player::input()
{
    // 가속도로 만들 것.
    if (GetAsyncKeyState(VK_RIGHT))
    {
        mX = (mX + mSpeed) * mVelocity;
    }
    if (GetAsyncKeyState(VK_LEFT))
    {
        mX--;
    }
    if (GetAsyncKeyState(VK_UP))
    {
        mY--;
    }
    if (GetAsyncKeyState(VK_DOWN))
    {
        mY++;
    }
    return false;
}