#include "Bug.h"
#include <algorithm>

Bug::Bug(D2DFramework* pFramework, Player* pPlayer) : Actor(pFramework, L"Images/Bugs.png")
{
    
    RECT rct;
    GetClientRect(pFramework->GetHWND(), &rct);
    mX = static_cast<float>(rand() % (rct.right - rct.left));
    mY = static_cast<float>(rand() % (rct.bottom - rct.top));

    mRotation = 0.0f;
    mIsDead = false;
    mSteps = 0.0f;
    mStage = 0;
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
    if (mStage == 0)
    {
        auto size = mpBitmap->GetPixelSize();
        auto PlayerSize = mpPlayer->Getsize();
        if (PlayerSize.width + Pos.x <= mX || Pos.x >= mX + size.width)
        {
            return false;
        }
        if (PlayerSize.height + Pos.y <= mY || Pos.y >= mY + size.height)
        {
            return false;
        }
        mIsDead = true;
        return true;
    }
}

void Bug::BugMovement(D2D_VECTOR_2F& Pos)
{
    ClamptheWall();
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
        // Å¸°Ù°ú ³ªÀÇ ºñÆ®¸Ê »çÀÌÁî °¡Á®¿À±â
        auto Playersize = mpPlayer->Getsize();
        auto mySize = mpBitmap->GetPixelSize();

        // Å¸°Ù ºñÆ®¸ÊÀÇ Áß½ÉÁÂÇ¥
        float TargetPosX = (Pos.x + Playersize.width) / 2;
        float TargetPosY = (Pos.y + Playersize.height) / 2;

        // ³ªÀÇ ºñÆ®¸Ê Áß½É ÁÂÇ¥
        float MyPosX = ((mX + mySize.width) / 2) + 8;
        float MyPosY = ((mY + mySize.height) / 2) + 8;
        D2D_VECTOR_2F vDistance = { TargetPosX - MyPosX, TargetPosY - MyPosY };

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

void Bug::ClamptheWall()
{
    RECT rect;
    GetClientRect(mpFramework->GetHWND(), &rect);
    if (mX <= rect.left || mX >= rect.right)
    {
        mRotation += 180.0f;
    }
    if (mY <= rect.top || mY >= rect.bottom)
    {
        mRotation += 180.0f;
    }
}

void Bug::Reset()
{
    RECT rect;
    GetClientRect(mpFramework->GetHWND(), &rect);
    
    RECT Range;
    GetClientRect(mpFramework->GetHWND(), &Range);
    Range.top = rect.top + 600.0f;
    Range.left = rect.left + 600.0f;
    Range.bottom = rect.bottom - 600.0f;
    Range.right = rect.right - 600.0f;


    auto Totalwidth = rect.right - rect.left;
    auto Totalheight = rect.bottom - rect.top;
    auto Rangewidth = Range.right - Range.left;
    auto Rangeheight = Range.bottom - Range.top;

    mX = static_cast<float>(rand() % (Totalwidth - Rangewidth));
    mY = static_cast<float>(rand() % (Totalheight - Rangeheight));
}
