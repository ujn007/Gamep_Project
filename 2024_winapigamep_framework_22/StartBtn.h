#pragma once
#include "Object.h"
class Texture;
class StartBtn : public Object
{
public:
	StartBtn();
	~StartBtn();
public:
	void Update() override;
	void Render(HDC _hdc) override;
	Vec2 GetRect();

private:
	Texture* m_pTex;
};