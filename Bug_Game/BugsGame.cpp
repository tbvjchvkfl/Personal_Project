#include "BugsGame.h"
#include "Bug.h"
#include "Player.h"

HRESULT BugsGame::Initialize(HINSTANCE hinstance, LPCWSTR title, UINT width, UINT height)
{
    HRESULT hr;
    hr = D2DFramework::Initialize(hinstance, title, width, height);
    ThrowIfFailed(hr, "Failed to D2DFramework::Initialize()");

    mspBackground = std::make_shared<Actor>(this, L"Images/back.png", 0.0f, 0.0f, 1.0f);
    mspUI = std::make_shared<UI_Box>(this);
    mspSubUI = std::make_shared<Actor>(this, L"Images/Sub_UI.png", 0.0f, 250.0f, 1.0f);
    mspPlayer = std::make_shared<Player>(this);
    for (int i = 0; i < 2; i++)
    {
        mBuglist.push_back(std::make_shared<Bug>(this, mspPlayer.get()));
    }
    mStage = 0;
    mGameStart = false;
    mGameClear = 0;
    time = 0;
    
    return S_OK;
}

void BugsGame::Render()
{
    mspRenderTarget->BeginDraw();
    mspRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
    mspRenderTarget->Clear(D2D1::ColorF(0.0f, 0.2f, 0.4f, 1.0f));
    
    //UI ·ÎÁ÷
    if (!mspUI->mNextStep)
    {
        mspBackground->Draw();
        mspUI->Draw();

        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
        {
            POINT pt;
            GetCursorPos(&pt);
            ScreenToClient(mHwnd, &pt);
            if (mspUI->IsClicked(pt))
            {
                mspUI->mNextStep = true;
            }
        }

        mspSubUI->Draw();
        WriteText(L"¹æÇâÅ°¸¦ ÀÌ¿ëÇÏ¿© ¹ú·¹ Ä³¸¯ÅÍ¸¦ ¿òÁ÷¿© ´Ù¸¥ ¹ú·¹µéÀ» Àâ¾Æ¸Ô´Â °ÔÀÓÀÔ´Ï´Ù.", 20, 280, 540, 100, L"¸¼Àº°íµñ", 25);
        WriteText(L"Á¦ÇÑ ½Ã°£¾È¿¡ ´Ù¸¥ ¹ú·¹¸¦ ¸ðµÎ Àâ¾Æ¸ÔÀ¸¼¼¿ä.", 20, 350, 800, 100, L"¸¼Àº°íµñ", 25);


        WriteText(L"GAME START", 40, 50, 800, 100, L"¸¼Àº°íµñ", 90);
    }

    // °ÔÀÓ ·ÎÁ÷
    if (mspUI->mNextStep)
    {
        mspBackground->Draw();
        if (!mGameStart)
        {
            if (time < 60)
            {
                WriteText(L"3", 480, 300, 80, 10, L"¸¼Àº°íµñ", 90);
                time++;
            }
            if (time >= 60 && time < 120)
            {
                WriteText(L"2", 480, 300, 80, 10, L"¸¼Àº°íµñ", 90);
                time++;
            }
            if (time >= 120 && time < 180)
            {
                WriteText(L"1", 480, 300, 80, 10, L"¸¼Àº°íµñ", 90);
                time++;
            }
            if (time >= 180 && time < 240)
            {
                WriteText(L"Game Start!", 280, 300, 800, 10, L"¸¼Àº°íµñ", 90);
                time++;
            }
            if (time >= 240)
            {
                mGameStart = true;
            }
        }
        
        if (mGameStart)
        {
            if (mStage == 0)
            {
                CheckCollision();
                for (auto& bug : mBuglist)
                {
                    bug->Draw();
                    bug->mStage = 0;
                }

                mspPlayer->Draw();
            }
            if (mGameClear == 1)
            {
                for (int i = 0; i < 20; i++)
                {
                    mBuglist.push_back(std::make_shared<Bug>(this, mspPlayer.get()));
                }
                mGameClear++;
            }
            if (mGameClear == 3)
            {
                WriteText(L"Game Clear!", 280, 300, 800, 10, L"¸¼Àº°íµñ", 90);
            }
            if (mStage == 1)
            {
                CheckBugs();
                for (auto& bug : mBuglist)
                {
                    bug->Draw();
                    bug->mStage = 1;
                }
                mspPlayer->Draw();
            }
        }
    }
    
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
    mspSubUI.reset();
    mspUI.reset();
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
    if (mBuglist.empty())
    {
        mStage++;
        mGameClear++;
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

    if (mBuglist.empty())
    {
        mStage++;
        mGameClear++;
    }
}