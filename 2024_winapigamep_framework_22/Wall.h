#pragma once
#include "Object.h"
class Texture;
class Wall : public Object
{
public:
	Wall();
	~Wall();
	void Update() override;
	void Render(HDC _hdc) override;
private:
	Texture* m_pTex;
};