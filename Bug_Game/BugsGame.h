#pragma once
#include <chrono>
#include <list>
#include <vector>
#include <memory>
#include "D2DFramework.h"
#include "Actor.h"
#include "Bug.h"
#include "UI_Box.h"

class BugsGame : public D2DFramework
{
private:
	std::list<std::shared_ptr<Bug>> mBuglist;
	std::shared_ptr<Actor> mspBackground;
	std::shared_ptr<Player> mspPlayer;
	std::shared_ptr<UI_Box> mspUI;
	std::shared_ptr<Actor> mspSubUI;
	

public:
	int mStage;
	bool mGameStart;
	bool mGameEnd;
	int mGameClear;
	int time;
public:
	virtual HRESULT Initialize(HINSTANCE hinstance, LPCWSTR title = L"BugsGame", UINT width = 1024, UINT height = 768) override;
	virtual void Render() override;
	virtual void Release() override;

	void CheckBugs();
	void CheckCollision();
	void PlayerIsDead();
};

