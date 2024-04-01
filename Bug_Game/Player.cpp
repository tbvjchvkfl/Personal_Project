#include "Player.h"

Player::Player(D2DFramework* pFramework) : Actor(pFramework, L"Images/Player.png")
{
    RECT rct;
    GetClientRect(pFramework->GetHWND(), &rct);
    
    mX = ((rct.left + rct.right) / 2.0f) - 50.0f;
    mY = ((rct.top + rct.bottom) / 2.0f) - 50.0f;

    mIsDead = false;
    mGravity = 9.3f;
    mVelocity = 1.0f;
    mStage = 0;
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
    if (mStage == 0)
    {
        RECT rect;
        GetClientRect(mpFramework->GetHWND(), &rect);
        auto Playersize = mpBitmap->GetPixelSize();

        // 가속도 (틈날 때 물리도 적용시켜보자!)
        if (GetAsyncKeyState(VK_RIGHT))
        {
            if (mX + Playersize.width >= rect.right)
            {
                mX = mX;
            }
            else
            {
                mVelocity += 0.2f;
                mX += mVelocity / mGravity;
            }
        }
        if (GetAsyncKeyState(VK_LEFT))
        {
            if (mX <= rect.left)
            {
                mX = mX;
            }
            else
            {
                mVelocity += 0.2f;
                mX -= mVelocity / mGravity;
            }
        }
        if (GetAsyncKeyState(VK_UP))
        {
            if (mY <= rect.top)
            {
                mY = mY;
            }
            else
            {
                mVelocity += 0.2f;
                mY -= mVelocity / mGravity;
            }
        }
        if (GetAsyncKeyState(VK_DOWN))
        {
            if (mY + Playersize.height >= rect.bottom)
            {
                mY = mY;
            }
            else
            {
                mVelocity += 0.2f;
                mY += mVelocity / mGravity;
            }
        }
        return false;
    }
}

bool Player::IsCollision(D2D_VECTOR_2F& Pos, D2D1_SIZE_U& bugsize)
{
    auto size = mpBitmap->GetPixelSize();
    if (bugsize.width + Pos.x <= mX || Pos.x >= mX + size.width)
    {
        return false;
    }
    if (bugsize.height + Pos.y <= mY || Pos.y >= mY + size.height)
    {
        return false;
    }
    mIsDead = true;
    return true;
}

void Player::Reset()
{
    RECT rct;
    GetClientRect(mpFramework->GetHWND(), &rct);

    mX = ((rct.left + rct.right) / 2.0f) - 50.0f;
    mY = ((rct.top + rct.bottom) / 2.0f) - 50.0f;

    mIsDead = false;
}

