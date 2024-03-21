#include "Bug.h"
#include <algorithm>
#include "Player.h"

Bug::Bug(D2DFramework* pFramework, Player* pPlayer) : Actor(pFramework, L"Images/Bugs.png")
{
    
    RECT rct;
    GetClientRect(pFramework->GetHWND(), &rct);
    mX = static_cast<float>(rand() % (rct.right - rct.left));
    mY = static_cast<float>(rand() % (rct.bottom - rct.top));

    if (mX < rct.left || mX > rct.right)
    {
        
    }

    mRotation = 0.0f;
    mIsDead = false;
    mSteps = 0.0f;
    mStage = 1;
    mpPlayer = pPlayer;
}

void Bug::Draw()
{
    auto pRT = mpFramework->GetRenderTarget();
    if (!pRT)
    {
        return;
    }
    auto size = mpBitmap->GetPixelSize();

    auto pPos = mpPlayer->GetPosition();
    BugMovement(pPos);

    auto matTranslate = D2D1::Matrix3x2F::Translation(mX, mY);
    auto matRotation = D2D1::Matrix3x2F::Rotation(mRotation, D2D_POINT_2F{ size.width * 0.5f, size.height * 0.5f });
    pRT->SetTransform(matRotation * matTranslate);


    D2D1_RECT_F rect{ 0,0,static_cast<float>(size.width), static_cast<float>(size.height) };
    pRT->DrawBitmap(mpBitmap, rect, mOpacity);
}

bool Bug::IsClicked(POINT& pt)
{
    auto size = mpBitmap->GetPixelSize();

    if (pt.x >= mX && pt.y >= mY && pt.x <= mX + size.width && pt.y <= mY + size.height)
    {
        mIsDead = true;
        return true;
    }

    return false;
}

bool Bug::IsCollision(D2D_VECTOR_2F& Pos)
{
    auto size = mpBitmap->GetPixelSize();
    
    if (Pos.x >= mX && Pos.y >= mY && Pos.x <= mX + size.width && Pos.y <= mY + size.height)
    {
        mIsDead = true;
        return true;
    }
    return false;
}

void Bug::BugMovement(D2D_VECTOR_2F& Pos)
{
    if (mStage == 0)
    {
        if (mSteps++ > 30)
        {
            mSteps = 0;
            mRotation += (1 - rand() % 3) * 45.0f;
        }

        auto forward = UPVECTOR * D2D1::Matrix3x2F::Rotation(mRotation);

        mX += forward.x;
        mY += forward.y;
    }
    if (mStage == 1)
    {
        D2D_VECTOR_2F vDistance = { Pos.x - mX, Pos.y - mY };

        float normal = sqrt(vDistance.x * vDistance.x + vDistance.y * vDistance.y);

        vDistance.x /= normal;
        vDistance.y /= normal;

        mX += vDistance.x;
        mY += vDistance.y;


        float targetRotation = atan2(vDistance.y, vDistance.x) * 180.0f / 3.14159265f;


        if (mRotation < targetRotation) {
            mRotation += 1.0f;
        }
        else if (mRotation > targetRotation) {
            mRotation -= 1.0f;
        }
    }
}

void Bug::WallCollision()
{
    RECT rect;
    GetClientRect(mpFramework->GetHWND(), &rect);
    
}

