#pragma once
#include"Object.h"
class Teleport : public Object
{
public:
	Teleport();
	~Teleport();
	void Update() override;
	void Render(HDC _hdc) override;

	void EnterCollision(Collider* _other)override;

	void SetTelePos(Vec2 pos) { m_teleportPos = pos; }
private :
	Vec2 m_teleportPos;	
};

