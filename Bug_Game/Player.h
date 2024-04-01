#pragma once
#include "Actor.h"

class Player : public Actor
{
private:
	const D2D_POINT_2F UPVECTOR{ 0.0f, 0.0f };

public:
	float mGravity;
	float mVelocity;
	bool mIsDead;
	int mStage;

public:
	Player(D2DFramework* pFramework);
	~Player();
	virtual void Draw() override;
	bool input();

	bool IsCollision(D2D_VECTOR_2F& Pos, D2D1_SIZE_U& bugsize);
	void Reset();
};

