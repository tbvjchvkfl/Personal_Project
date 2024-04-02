#pragma once
#include "Actor.h"
#include "Player.h"
#include <memory>

class Bug : public Actor
{
private:
	const D2D_POINT_2F UPVECTOR{ 0.0f, -1.0f };
	float mRotation;
	Player* mpPlayer;

public:
	bool mIsDead;
	float mSteps;
	int mStage;

public:
	Bug(D2DFramework* pFramework, Player* pPlayer);
	virtual void Draw() override;
	bool IsClicked(POINT& pt);
	bool IsCollision(D2D_VECTOR_2F& Pos);
	void BugMovement(D2D_VECTOR_2F& Pos);
	void ClamptheWall();
	void Reset();
};

