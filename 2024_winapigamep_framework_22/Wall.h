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
	void EnterCollision(Collider* _other)override;
	void StayCollision(Collider* _other) override;
	void ExitCollision(Collider* _other) override;
public:
	void SetCollider(Object* owner, Vec2 scale, Vec2 offset);
private:
	Texture* m_pTex;
};