#pragma once
#include <chrono>
#include <list>
#include <memory>
#include "D2DFramework.h"
#include "Actor.h"

class BugsGame : public D2DFramework
{
private:
	std::list<std::shared_ptr<Actor>> mBuglist;
	std::shared_ptr<Actor> mspBackground;
	std::shared_ptr<Actor> mspPlayer;


public:
	virtual HRESULT Initialize(HINSTANCE hinstance, LPCWSTR title = L"BugsGame", UINT width = 1024, UINT height = 768) override;
	virtual void Render() override;
	virtual void Release() override;

	void CheckBugs();
	void CheckCollision();
};

