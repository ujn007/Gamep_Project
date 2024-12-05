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

	/*void EnterCollision(Collider* _other)override;
	void StayCollision(Collider* _other) override;
	void ExitCollision(Collider* _other) override;*/

	void HandleMovement();
	void HandleAnimation();

	void SetIsJump(bool v) { isJump = v; }
	void SetIsGround(bool v) { isGround = v; }

	RigidBody* GetRigid() { return rigid; }	
private:
	RigidBody* rigid;
	Texture* m_pTex;
	ANIM currentAnim;
	COLDIR currentCol;
	bool isJump;
	bool isGround;
	bool isFacingRight;
	bool isLeftCollision;
	bool isRightCollision;
};

