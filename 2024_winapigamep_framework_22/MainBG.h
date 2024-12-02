#pragma once
#include "Object.h"
class Texture;
class MainBG : public Object
{
public:
	MainBG();
	~MainBG();
public:
	void Update() override;
	void Render(HDC _hdc) override;
private:
	Texture* m_pTex;
};
