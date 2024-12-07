#pragma once
#include "Object.h"
class Texture;
class Btn : public Object
{
public:
	Btn();
	Btn(wstring name, wstring path, wstring loadScene);
	~Btn();
public:
	void Update() override;
	void Render(HDC _hdc) override;
	Vec2 GetRect();

private:
	Texture* m_pTex;
	wstring _loadScene;
};