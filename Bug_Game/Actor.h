#pragma once
#include "D2DFramework.h"

class Actor
{
protected:
	D2DFramework* mpFramework;
	ID2D1Bitmap* mpBitmap;

	float mX;
	float mY;
	float mOpacity;

public:
	Actor() = delete;
	Actor(D2DFramework* pFramework, LPCWSTR filename);
	Actor(D2DFramework* pFramework, LPCWSTR filename, float x, float y, float opacity = 1.0f);
	
	virtual ~Actor();

private:
	void Draw(float x, float y, float opacity);

public:
	virtual void Draw();
	inline D2D_VECTOR_2F GetPosition() { return { mX, mY }; }
	inline D2D1_SIZE_U Getsize() { return mpBitmap->GetPixelSize(); }
	inline void SetPositioin(const D2D_VECTOR_2F& pos) { mX = pos.x; mY = pos.y; }
	inline void SetPosition(float x, float y) { mX = x; mY = y; }
};