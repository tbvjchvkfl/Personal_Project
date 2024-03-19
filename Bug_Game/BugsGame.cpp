#include "BugsGame.h"
#include "Bug.h"
#include "Player.h"

HRESULT BugsGame::Initialize(HINSTANCE hinstance, LPCWSTR title, UINT width, UINT height)
{
    HRESULT hr;
    hr = D2DFramework::Initialize(hinstance, title, width, height);
    ThrowIfFailed(hr, "Failed to D2DFramework::Initialize()");

    mspBackground = std::make_shared<Actor>(this, L"Images/back.png", 0.0f, 0.0f, 1.0f);
    mspPlayer = std::make_shared<Player>(this);
    for (int i = 0; i < 40; i++)
    {
        mBuglist.push_back(std::make_shared<Bug>(this, mspPlayer.get()));
    }
    mStage = 0;
    return S_OK;
}

void BugsGame::Render()
{
    mspRenderTarget->BeginDraw();
    mspRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
    mspRenderTarget->Clear(D2D1::ColorF(0.0f, 0.2f, 0.4f, 1.0f));
    
    CheckBugs();
    CheckCollision();

    mspBackground->Draw();
    
    for (auto& bug : mBuglist)
    {
        bug->Draw();
    }


    mspPlayer->Draw();
    HRESULT hr = mspRenderTarget->EndDraw();

    if (hr == D2DERR_RECREATE_TARGET)
    {
        CreateDeviceResources();
    }
}

void BugsGame::Release()
{
    for (auto& bug : mBuglist)
    {
        bug.reset();
    }

    mBuglist.clear();
    mspPlayer.reset();
    mspBackground.reset();

    D2DFramework::Release();
}

void BugsGame::CheckBugs()
{
    if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
    {
        POINT pt;
        GetCursorPos(&pt);
        ScreenToClient(mHwnd, &pt);

        auto itr = std::remove_if(mBuglist.begin(), mBuglist.end(),
            [&](auto& actor)
            {
                Bug* p = static_cast<Bug*>(actor.get());
                p->IsClicked(pt);

                if (p->mIsDead)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        );
        mBuglist.erase(itr, mBuglist.end());
    } 
}

void BugsGame::CheckCollision()
{
    auto PlayerPosition = mspPlayer->GetPosition();
    auto list_iterator = std::remove_if(mBuglist.begin(), mBuglist.end(),
               [&](auto& actor)
               {
                   Bug* p = static_cast<Bug*>(actor.get());
                   
                   return p->IsCollision(PlayerPosition);
               }
           );
           mBuglist.erase(list_iterator, mBuglist.end());
}

void BugsGame::Bug_Move()
{
    auto Pos = mspPlayer->GetPosition();

    for (auto& bug : mBuglist)
    {
        auto bPos = bug->GetPosition();
        
    }
}

