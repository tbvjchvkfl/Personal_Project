#pragma once
#include "Actor.h"
class Player : public Actor
{
private:
	const D2D_POINT_2F UPVECTOR{ 0.0f, 0.0f };

public:
	float mSpeed;
	float mVelocity;

public:
	Player(D2DFramework* pFramework);
	~Player();
	virtual void Draw() override;
	bool input();
};

