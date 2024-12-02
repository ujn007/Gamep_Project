#pragma once
#include "Object.h"
#include "RigidBody.h"
class Texture;
class Player : public Object
{
public:
	Player();
	~Player();
public:
	void Update() override;
	void Render(HDC _hdc) override;	

	void EnterCollision(Collider* _other)override;
	void StayCollision(Collider* _other) override;
	void ExitCollision(Collider* _other) override;
private:
	RigidBody* rigid;
	Texture* m_pTex;
	bool isJump;
	bool isGround;
};

