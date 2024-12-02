#pragma once
#include "Object.h"
class Texture;
class Quit : public Object
{
public:
	Quit();
	~Quit();
public:
	void Update() override;
	void Render(HDC _hdc) override;
	Vec2 GetRect();

private:
	Texture* m_pTex;
};